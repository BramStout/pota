#include <string>
#include <vector>
#include <cstdlib>

#include <ai.h>
#include <stdio.h>

// Swaps the filter of the RGBA aov to a lentil_debug_filter for visualizing the to-be-redistributed samples


AI_OPERATOR_NODE_EXPORT_METHODS(LentilFilterDebugOperatorMtd);


std::vector<std::string> split_str(std::string str, std::string token)
{
    std::vector<std::string>result;
    while(str.size())
    {
        int index = static_cast<int>(str.find(token));
        
        if(index != std::string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index+token.size());
            
            if(str.size() == 0)
                result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


enum {
    p_debug_luminance_filter
};


struct OpData
{
    AtNode *camera_node;
    AtNode *lentil_debug_filter;
    AtString camera_node_type;
    bool cook;
};

node_parameters {}

operator_init
{
    OpData* data = (OpData*)AiMalloc(sizeof(OpData));

    data->camera_node = AiUniverseGetCamera();
    const AtNodeEntry *nentry = AiNodeGetNodeEntry(data->camera_node);
    data->camera_node_type = AtString(AiNodeEntryGetName(nentry));

    data->cook = false;

    if (data->camera_node_type == AtString("lentil_thinlens") || data->camera_node_type == AtString("lentil")){
        data->lentil_debug_filter = AiNode("lentil_debug_filter", AtString("lentil_debug_filter"));
        data->cook = true;
    }

    AiNodeSetLocalData(op, data);  
    return true;
}

operator_cook
{
    OpData* data = (OpData*)AiNodeGetLocalData(op);

    if (data->cook == false) return false;
    
    AtNode* options = AiUniverseGetOptions();
    AtArray* outputs = AiNodeGetArray(options, "outputs");

    int offset = 0;
    int elements = AiArrayGetNumElements(outputs);

    for (int i=0; i<elements; ++i) {
        std::string output_string = AiArrayGetStr(outputs, i).c_str();
        std::string aov_name = split_str(output_string, std::string(" ")).at(0);
        if (aov_name == "RGBA"){
            std::string filter = split_str(output_string, std::string(" ")).at(elements); // get one before last element
            output_string.replace(output_string.find(filter), filter.length(), AiNodeGetStr(data->lentil_debug_filter, "name"));
            AiArraySetStr(outputs, i, AtString(output_string.c_str()));
        }
    }
  
    return true;
}

operator_post_cook
{
    return true;
}

operator_cleanup
{
    OpData* data = (OpData*)AiNodeGetLocalData(op);
    AiFree(data);
    return true;
}

node_loader
{
    if (i>0) return 0;
    node->methods = (AtNodeMethods*)LentilFilterDebugOperatorMtd;
    node->name = "lentil_filter_debug_operator";
    node->node_type = AI_NODE_OPERATOR;
    strcpy(node->version, AI_VERSION);
    return true;
}