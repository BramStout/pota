// initially try to only do it for rgba, support multiple aovs at later point
// doesn't seem to like AA_samples at 1 .. takes long?
// add image based bokeh & chromatic aberrations & optical vignetting to backtracing
// strange behaviour when rendering multiple images after each other.. buffer doesn't seem to be cleared
// filter is losing 40% of the energy, look into how these actually work

// circle of confusion on sensor is just ...slightly... bigger
// compute analytical size of circle of confusion

#include <ai.h>
#include <vector>
#include "lentil_thinlens.h"

#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"

 
AI_DRIVER_NODE_EXPORT_METHODS(ThinLensBokehDriverMtd);
 
struct ThinLensBokehDriver {
  int xres;
  int yres;
  int samples;
  int aa_samples;
  bool enabled;
  float filter_width;
  std::vector<AtRGBA> image;
  AtMatrix world_to_camera_matrix;
};


float gaussian(AtVector2 p, float width) {
    /* matches Arnold's exactly. */
    /* Sharpness=2 is good for width 2, sigma=1/sqrt(8) for the width=4,sharpness=4 case */
    // const float sigma = 0.5f;
    // const float sharpness = 1.0f / (2.0f * sigma * sigma);

    p /= (width * 0.5f);
    float dist_squared = (p.x * p.x + p.y * p.y);
    if (dist_squared > (1.0f)) {
        return 0.0f;
    }

    // const float normalization_factor = 1;
    // Float weight = normalization_factor * expf(-dist_squared * sharpness);

    float weight = AiFastExp(-dist_squared * 2.0f); // was:

    if (weight > 0.0f) {
        return weight;
    } else {
        return 0.0f;
    }
}


node_parameters {}
 
node_initialize
{
  AiNodeSetLocalData(node, new ThinLensBokehDriver());

  static const char *required_aovs[] = {"RGBA RGBA", "VECTOR P", NULL};
  AiRawDriverInitialize(node, required_aovs, false);
}
 
node_update 
{
  ThinLensBokehDriver *bokeh = (ThinLensBokehDriver*)AiNodeGetLocalData(node);
  CameraThinLens *tl = (CameraThinLens*)AiNodeGetLocalData(AiUniverseGetCamera());
  
  // disable for non-lentil cameras
  AtNode *node_camera = AiUniverseGetCamera();
  AiNodeIs(node_camera, AtString("lentil_thinlens")) ? bokeh->enabled = true : bokeh->enabled = false;
  
  // get general options
  bokeh->xres = AiNodeGetInt(AiUniverseGetOptions(), "xres");
  bokeh->yres = AiNodeGetInt(AiUniverseGetOptions(), "yres");
  bokeh->filter_width = AiNodeGetFlt(AiUniverseGetOptions(), "filter_width");
  bokeh->aa_samples = AiNodeGetInt(AiUniverseGetOptions(), "AA_samples");

  AiWorldToCameraMatrix(AiUniverseGetCamera(), AiCameraGetShutterStart(), bokeh->world_to_camera_matrix); // can i use sg->time? do i have access to shaderglobals? setting this to a constant might disable motion blur..
  
  // construct buffer
  bokeh->image.clear();
  bokeh->image.reserve(bokeh->xres * bokeh->yres);
}
 
driver_supports_pixel_type { return true; } // not needed for raw drivers
 
driver_open {}
 
driver_extension
{
   static const char *extensions[] = {"raw", NULL};
   return extensions;
}
 
driver_needs_bucket
{
   return true; // API: true if the bucket needs to be rendered, false if it can be skipped
}
 
driver_prepare_bucket {} // called before a bucket is rendered
 
driver_process_bucket
{
  ThinLensBokehDriver *bokeh = (ThinLensBokehDriver*)AiNodeGetLocalData(node);
  CameraThinLens *tl = (CameraThinLens*)AiNodeGetLocalData(AiUniverseGetCamera());

  if (!bokeh->enabled) return;
  
  const double xres = (double)bokeh->xres;
  const double yres = (double)bokeh->yres;
  const double frame_aspect_ratio = xres/yres;

  for (int py = bucket_yo; py < bucket_yo + bucket_size_y; py++) {
		for (int px = bucket_xo; px < bucket_xo + bucket_size_x; px++) {

      AiAOVSampleIteratorInitPixel(sample_iterator, px, py);
			while (AiAOVSampleIteratorGetNext(sample_iterator)) {
				AtRGBA sample = AiAOVSampleIteratorGetRGBA(sample_iterator);
        AtVector sample_pos_ws = AiAOVSampleIteratorGetAOVVec(sample_iterator, AtString("P"));
        float inv_density = AiAOVSampleIteratorGetInvDensity(sample_iterator);
        if (inv_density <= 0.f) continue; // does this every happen? test
        
        float sample_luminance = sample.r*0.21 + sample.g*0.71 + sample.b*0.072;
        
      // GAUSSIAN FILTER
        //float filter_width = 1.8;
        //const AtVector2& offset = AiAOVSampleIteratorGetOffset(sample_iterator);
        //sample *= gaussian(offset, filter_width) * inv_density;
        sample *= inv_density;




      // ENERGY REDISTRIBUTION
        if (sample_luminance > tl->minimum_rgb) {

          // convert sample world space position to camera space

          Eigen::Vector2d sensor_position;
          AtVector camera_space_sample_position = AiM4PointByMatrixMult(bokeh->world_to_camera_matrix, sample_pos_ws);
          

        // PROBE RAYS samples to determine size of bokeh & subsequent sample count
          AtVector2 bbox_min (0, 0);
          AtVector2 bbox_max (0, 0);
          for(int count=0; count<128; count++) {
            Eigen::Vector2d unit_disk(0, 0);
            float r1 = xor128() / 4294967296.0;
            float r2 = xor128() / 4294967296.0;
            concentricDiskSample(r1, r2, unit_disk, 0.8, 0.0, 1.0);
            unit_disk *= -1.0;
            
            // tmp copy
            AtVector2 lens(unit_disk(0), unit_disk(1));
            
            // scale points in [-1, 1] domain to actual aperture radius
            lens *= tl->aperture_radius / tl->focus_distance;
            AtVector lens3d(lens.x, lens.y, 0.0);

            // intersect at -1? z plane.. this could be the sensor?
            AtVector dir = AiV3Normalize(camera_space_sample_position - lens3d);
            float intersection = std::abs(1.0 / dir.z);
            AtVector sensor_position = (lens3d + (dir*intersection)) / tl->tan_fov; // could be so wrong, most likely inaccurate
            

            // convert sensor position to pixel position
            Eigen::Vector2d s(sensor_position.x / (tl->sensor_width * 0.5), sensor_position.y / (tl->sensor_width * 0.5) * frame_aspect_ratio);
            const float pixel_x = (( s(0) + 1.0) / 2.0) * xres;
            const float pixel_y = ((-s(1) + 1.0) / 2.0) * yres;

            // expand bbox
            if (count == 0) {
              bbox_min[0] = pixel_x;
              bbox_min[1] = pixel_y;
              bbox_max[0] = pixel_x;
              bbox_max[1] = pixel_y;
            } else {
              if (pixel_x < bbox_min[0]) bbox_min[0] = pixel_x;
              if (pixel_y < bbox_min[1]) bbox_min[1] = pixel_y;
              if (pixel_x > bbox_max[0]) bbox_max[0] = pixel_x;
              if (pixel_y > bbox_max[1]) bbox_max[1] = pixel_y;
            }
          }

          double bbox_area = (bbox_max[0] - bbox_min[0]) * (bbox_max[1] - bbox_min[1]);
          int samples = std::floor(bbox_area * 20.0);

          // need to calculate sample count here!!
          // int samples = 200000;
          samples = std::ceil((double)(samples) / (double)(bokeh->aa_samples*bokeh->aa_samples));

          sample /= (double)(samples);

          int total_samples_taken = 0;
          int max_total_samples = samples*1.5;
          for(int count=0; count<samples && total_samples_taken < max_total_samples; count++) {
            ++total_samples_taken;

            // either get uniformly distributed points on the unit disk or bokeh image
            Eigen::Vector2d unit_disk(0, 0);

            float r1 = xor128() / 4294967296.0;
            float r2 = xor128() / 4294967296.0;

            if (tl->use_image) {
                tl->image.bokehSample(r1, r2, unit_disk);
            } else {
                concentricDiskSample(r1, r2, unit_disk, tl->bias, tl->square, tl->squeeze);
            }

            unit_disk(0) *= tl->squeeze;
            unit_disk *= -1.0;
            
            // tmp copy
            AtVector2 lens(unit_disk(0), unit_disk(1));
            
            // scale points in [-1, 1] domain to actual aperture radius
            lens *= tl->aperture_radius / tl->focus_distance;
            AtVector lens3d(lens.x, lens.y, 0.0);

            // intersect at -1? z plane.. this could be the sensor?
            AtVector dir = AiV3Normalize(camera_space_sample_position - lens3d);
            float intersection = std::abs(1.0 / dir.z);
            AtVector sensor_position = (lens3d + (dir*intersection)) / tl->tan_fov; // could be so wrong, most likely inaccurate
            
            // add optical vignetting here
            if (tl->optical_vignetting_distance > 0.0){
              if (!empericalOpticalVignetting(lens3d, dir, tl->aperture_radius/tl->focus_distance, tl->optical_vignetting_radius, tl->optical_vignetting_distance/tl->focus_distance)){ //why doesn't this work? 
                  --count;
                  continue;
              }
            }


            // convert sensor position to pixel position
            Eigen::Vector2d s(sensor_position[0], 
                              sensor_position[1] * frame_aspect_ratio);

            const float pixel_x = (( s(0) + 1.0) / 2.0) * xres;
            const float pixel_y = ((-s(1) + 1.0) / 2.0) * yres;

            // if outside of image
            if ((pixel_x >= xres) || 
                (pixel_x < 0)    || 
                (pixel_y >= yres) || 
                (pixel_y < 0))
            {
              --count; // really need something better here, many samples are wasted outside of frame
              continue;
            }

            // write sample to image
            int pixelnumber = static_cast<int>(bokeh->xres * floor(pixel_y) + floor(pixel_x));
            bokeh->image[pixelnumber] += sample;
          }
        }

        else { // COPY ENERGY IF NO REDISTRIBUTION IS REQUIRED
          int pixelnumber = static_cast<int>(bokeh->xres * py + px);
          bokeh->image[pixelnumber] += sample;
        }
      }
    }
  }
}
 
driver_write_bucket {}
 
driver_close
{
  ThinLensBokehDriver *bokeh = (ThinLensBokehDriver*)AiNodeGetLocalData(node);
  CameraThinLens *tl = (CameraThinLens*)AiNodeGetLocalData(AiUniverseGetCamera());  

  if (!bokeh->enabled) return;

  // dump framebuffer to exr
  std::vector<float> image(bokeh->yres * bokeh->xres * 4);
  int offset = -1;
  int pixelnumber = 0;

  for(auto i = 0; i < bokeh->xres * bokeh->yres; i++){
    image[++offset] = bokeh->image[pixelnumber].r;
    image[++offset] = bokeh->image[pixelnumber].g;
    image[++offset] = bokeh->image[pixelnumber].b;
    image[++offset] = bokeh->image[pixelnumber].a;
    ++pixelnumber;
  }

  SaveEXR(image.data(), bokeh->xres, bokeh->yres, 4, 0, tl->bokeh_exr_path.c_str());
  AiMsgWarning("[LENTIL] Bokeh AOV written to %s", tl->bokeh_exr_path.c_str());
}
 
node_finish
{
   ThinLensBokehDriver *bokeh = (ThinLensBokehDriver*)AiNodeGetLocalData(node);
   delete bokeh;
}

node_loader
{
   if (i>0) return false;
   node->methods = (AtNodeMethods*) ThinLensBokehDriverMtd;
   node->output_type = AI_TYPE_NONE;
   node->name = "lentil_thin_lens_bokeh_driver";
   node->node_type = AI_NODE_DRIVER;
   strcpy(node->version, AI_VERSION);
   return true;
}
 