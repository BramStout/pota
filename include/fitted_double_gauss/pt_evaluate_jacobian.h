const float dx00 =  + 0.592582  + 0.0499465 *lambda + 0.0323359 *y*dy + 0.0758095 *x*dx + -0.0389817 *lens_ipow(lambda, 2) + 0.000142213 *lens_ipow(y, 2) + 0.000427304 *lens_ipow(x, 2) + 1.67656 *lens_ipow(dy, 2) + 1.81407 *lens_ipow(dx, 2) + 0.0713542 *y*lens_ipow(dy, 3)*lambda + 0.00125855 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + -3.55319 *lens_ipow(dx, 4)*lambda + -1.59678e-05 *lens_ipow(x, 2)*y*dy*lambda + 0.00306845 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lambda + -1.18104e-09 *lens_ipow(x, 2)*lens_ipow(y, 4)*lambda + 7.97509e-08 *lens_ipow(x, 5)*dx*lambda + -5.40693e-08 *x*lens_ipow(y, 4)*dx*lambda+0.0f;
const float dx01 =  + 0.0323359 *x*dy + 0.000284425 *x*y + 0.0114145 *y*dx + 0.677473 *dx*dy*lambda + -0.536195 *dx*dy*lens_ipow(lambda, 2) + 0.0713542 *x*lens_ipow(dy, 3)*lambda + 0.0025171 *x*y*lens_ipow(dy, 2)*lambda + -0.000798207 *lens_ipow(y, 2)*dx*dy*lambda + -5.3226e-06 *lens_ipow(x, 3)*dy*lambda + -1.57472e-09 *lens_ipow(x, 3)*lens_ipow(y, 3)*lambda + -1.08139e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*lambda+0.0f;
const float dx02 =  + 100.12  + -0.811097 *lambda + 0.0379048 *lens_ipow(x, 2) + -128.198 *lens_ipow(dx, 2) + 3.62815 *x*dx + 0.00570726 *lens_ipow(y, 2) + -209.372 *lens_ipow(dy, 2)*lambda + 0.677473 *y*dy*lambda + -0.536195 *y*dy*lens_ipow(lambda, 2) + 299.926 *lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -14.2128 *x*lens_ipow(dx, 3)*lambda + 666.95 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + -0.000266069 *lens_ipow(y, 3)*dy*lambda + 0.00204563 *lens_ipow(x, 3)*dx*lambda + -168.54 *lens_ipow(dy, 2)*lens_ipow(lambda, 4) + 1.32918e-08 *lens_ipow(x, 6)*lambda + -2.70347e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)*lambda+0.0f;
const float dx03 =  + 0.0323359 *x*y + 3.35312 *x*dy + -418.745 *dx*dy*lambda + 0.677473 *y*dx*lambda + -0.536195 *y*dx*lens_ipow(lambda, 2) + 599.852 *dx*dy*lens_ipow(lambda, 2) + 0.214063 *x*y*lens_ipow(dy, 2)*lambda + 0.0025171 *x*lens_ipow(y, 2)*dy*lambda + 444.634 *lens_ipow(dx, 3)*dy*lambda + -0.000266069 *lens_ipow(y, 3)*dx*lambda + -5.3226e-06 *lens_ipow(x, 3)*y*lambda + -337.08 *dx*dy*lens_ipow(lambda, 4)+0.0f;
const float dx04 =  + 0.0499465 *x + -0.811097 *dx + -0.0779634 *x*lambda + -209.372 *dx*lens_ipow(dy, 2) + 0.677473 *y*dx*dy + -1.07239 *y*dx*dy*lambda + 599.852 *dx*lens_ipow(dy, 2)*lambda + 0.0713542 *x*y*lens_ipow(dy, 3) + 0.00125855 *x*lens_ipow(y, 2)*lens_ipow(dy, 2) + -3.55319 *x*lens_ipow(dx, 4) + 222.317 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + -0.000266069 *lens_ipow(y, 3)*dx*dy + -5.3226e-06 *lens_ipow(x, 3)*y*dy + 0.00102282 *lens_ipow(x, 3)*lens_ipow(dx, 2) + -674.159 *dx*lens_ipow(dy, 2)*lens_ipow(lambda, 3) + -3.93679e-10 *lens_ipow(x, 3)*lens_ipow(y, 4) + 1.32918e-08 *lens_ipow(x, 6)*dx + -2.70347e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)*dx+0.0f;
const float dx10 =  + 0.153878 *dx*dy + 0.0314574 *y*dx + 0.00028279 *x*y + 0.0114526 *x*dy + 0.000470037 *x*y*lens_ipow(dy, 2)*lambda + -0.000286802 *x*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -3.92486e-10 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const float dx11 =  + 0.588556  + 0.0557925 *lambda + 1.62675 *lens_ipow(dx, 2) + 0.0917521 *y*dy + 2.49363 *lens_ipow(dy, 2) + 0.0314574 *x*dx + -0.0358604 *lens_ipow(lambda, 2) + 0.000141395 *lens_ipow(x, 2) + 0.000536645 *lens_ipow(y, 2) + -1.35881 *lens_ipow(dy, 2)*lambda + -0.0337057 *y*dy*lambda + -0.00020644 *lens_ipow(y, 2)*lambda + 3.6432e-05 *lens_ipow(y, 3)*dy + 0.149706 *y*lens_ipow(dy, 3) + 0.000670628 *lens_ipow(y, 2)*lens_ipow(dx, 2) + 0.0048425 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 0.000235019 *lens_ipow(x, 2)*lens_ipow(dy, 2)*lambda + 1.3627 *y*lens_ipow(dx, 4)*dy + -0.000286802 *lens_ipow(x, 2)*y*lens_ipow(dx, 2)*dy + -2.94364e-10 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const float dx12 =  + 3.2535 *y*dx + 0.153878 *x*dy + 0.0314574 *x*y + -84.1934 *dx*dy + 240.344 *dx*lens_ipow(dy, 3) + 0.000447085 *lens_ipow(y, 3)*dx + 2.7254 *lens_ipow(y, 2)*lens_ipow(dx, 3)*dy + -0.000286802 *lens_ipow(x, 2)*lens_ipow(y, 2)*dx*dy+0.0f;
const float dx13 =  + 99.6889  + 0.045876 *lens_ipow(y, 2) + 4.98727 *y*dy + 0.153878 *x*dx + -42.0967 *lens_ipow(dx, 2) + 0.00572629 *lens_ipow(x, 2) + -2.71763 *y*dy*lambda + -405.945 *lens_ipow(dy, 2)*lambda + -0.0168528 *lens_ipow(y, 2)*lambda + 360.516 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 9.10801e-06 *lens_ipow(y, 4) + 0.224559 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 319.698 *lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 0.00322833 *lens_ipow(y, 3)*dy + 0.000470037 *lens_ipow(x, 2)*y*dy*lambda + 0.681351 *lens_ipow(y, 2)*lens_ipow(dx, 4) + -0.000143401 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dx, 2) + -169.965 *lens_ipow(dy, 2)*lens_ipow(lambda, 6)+0.0f;
const float dx14 =  + 0.0557925 *y + -0.0717209 *y*lambda + -1.35881 *y*lens_ipow(dy, 2) + -135.315 *lens_ipow(dy, 3) + -0.0168528 *lens_ipow(y, 2)*dy + -6.88134e-05 *lens_ipow(y, 3) + 213.132 *lens_ipow(dy, 3)*lambda + 0.000235019 *lens_ipow(x, 2)*y*lens_ipow(dy, 2) + -339.929 *lens_ipow(dy, 3)*lens_ipow(lambda, 5)+0.0f;
const float dx20 =  + -0.0282279  + -0.000260254 *lambda + -0.00214261 *y*dy + -0.00068755 *x*dx + -6.63026e-06 *lens_ipow(y, 2) + -0.144619 *lens_ipow(dy, 2) + -0.0045328 *lens_ipow(dx, 2) + -2.31173e-05 *lens_ipow(x, 2)*lens_ipow(lambda, 2) + 9.70971e-05 *lens_ipow(x, 2)*lens_ipow(lambda, 4) + -0.00163849 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.549814 *x*dx*lens_ipow(dy, 4) + 49.9949 *lens_ipow(dx, 2)*lens_ipow(dy, 4) + -1.4523e-05 *lens_ipow(x, 2)*y*lens_ipow(dy, 3) + -8.51808e-05 *lens_ipow(x, 2)*lens_ipow(lambda, 5) + -543.956 *lens_ipow(dx, 2)*lens_ipow(dy, 6) + -6.84923 *x*dx*lens_ipow(dy, 6) + -0.151143 *lens_ipow(x, 2)*lens_ipow(dy, 8)+0.0f;
const float dx21 =  + -0.193971 *dx*dy + -0.00214261 *x*dy + -1.32605e-05 *x*y + -0.00126353 *y*dx + -0.239743 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -0.00327698 *x*y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -4.84099e-06 *lens_ipow(x, 3)*lens_ipow(dy, 3) + 6.17393e-06 *lens_ipow(y, 3)*lens_ipow(dx, 3)*lambda+0.0f;
const float dx22 =  + -3.05455  + 0.150251 *lambda + -0.193971 *y*dy + -0.000343775 *lens_ipow(x, 2) + 3.8659 *lens_ipow(dx, 2) + -13.7923 *lens_ipow(dy, 2) + -0.00906559 *x*dx + -0.000631766 *lens_ipow(y, 2) + -0.108421 *lens_ipow(lambda, 2) + -0.359615 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 7371.43 *lens_ipow(dx, 2)*lens_ipow(dy, 4) + -0.00327698 *x*lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 0.274907 *lens_ipow(x, 2)*lens_ipow(dy, 4) + 99.9898 *x*dx*lens_ipow(dy, 4) + 4.63044e-06 *lens_ipow(y, 4)*lens_ipow(dx, 2)*lambda + -1087.91 *x*dx*lens_ipow(dy, 6) + -3.42461 *lens_ipow(x, 2)*lens_ipow(dy, 6) + -75326.9 *lens_ipow(dx, 2)*lens_ipow(dy, 6)+0.0f;
const float dx23 =  + -0.193971 *y*dx + -0.00214261 *x*y + -27.5846 *dx*dy + -0.289237 *x*dy + -0.239743 *lens_ipow(y, 2)*lens_ipow(dx, 3)*dy + 9828.58 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + -0.00327698 *x*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 1.09963 *lens_ipow(x, 2)*dx*lens_ipow(dy, 3) + 199.98 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3) + -1.4523e-05 *lens_ipow(x, 3)*y*lens_ipow(dy, 2) + -3263.74 *x*lens_ipow(dx, 2)*lens_ipow(dy, 5) + -20.5477 *lens_ipow(x, 2)*dx*lens_ipow(dy, 5) + -150654 *lens_ipow(dx, 3)*lens_ipow(dy, 5) + -0.403049 *lens_ipow(x, 3)*lens_ipow(dy, 7)+0.0f;
const float dx24 =  + -0.000260254 *x + 0.150251 *dx + -0.216841 *dx*lambda + -1.54115e-05 *lens_ipow(x, 3)*lambda + 0.000129463 *lens_ipow(x, 3)*lens_ipow(lambda, 3) + 1.54348e-06 *lens_ipow(y, 4)*lens_ipow(dx, 3) + -0.000141968 *lens_ipow(x, 3)*lens_ipow(lambda, 4)+0.0f;
const float dx30 =  + 0.278569 *dx*dy + 0.000913623 *y*dx + 1.01635e-05 *x*y + 0.0023533 *x*dy + -0.391177 *lens_ipow(dx, 3)*dy + -5.96864e-07 *lens_ipow(y, 3)*dx + 1.32679 *dx*lens_ipow(dy, 3) + 0.0182734 *y*dx*lens_ipow(dy, 2) + -6.39725e-09 *x*lens_ipow(y, 3) + 0.0147764 *x*lens_ipow(dy, 3) + 5.32368e-05 *lens_ipow(x, 2)*dx*dy + 0.000207444 *x*y*lens_ipow(dy, 2)+0.0f;
const float dx31 =  + -0.0282638  + -0.000273248 *lambda + 0.0476166 *lens_ipow(dx, 2) + -0.00056558 *y*dy + 0.000913623 *x*dx + 5.08174e-06 *lens_ipow(x, 2) + -3.89906e-06 *lens_ipow(y, 2)*lambda + -1.79059e-06 *x*lens_ipow(y, 2)*dx + 0.0182734 *x*dx*lens_ipow(dy, 2) + -9.59588e-09 *lens_ipow(x, 2)*lens_ipow(y, 2) + -8.36641e-05 *lens_ipow(y, 2)*lens_ipow(dx, 2) + 0.786317 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.000103722 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 7.18995e-06 *lens_ipow(y, 2)*lens_ipow(lambda, 5)+0.0f;
const float dx32 =  + 0.0952333 *y*dx + 0.278569 *x*dy + 0.000913623 *x*y + 32.3428 *dx*dy + -1.17353 *x*lens_ipow(dx, 2)*dy + 116.258 *dx*lens_ipow(dy, 3) + -5.96864e-07 *x*lens_ipow(y, 3) + 1.32679 *x*lens_ipow(dy, 3) + 0.0182734 *x*y*lens_ipow(dy, 2) + -5.57761e-05 *lens_ipow(y, 3)*dx + 1.57263 *y*dx*lens_ipow(dy, 2) + 1.77456e-05 *lens_ipow(x, 3)*dy + -93.1076 *lens_ipow(dx, 3)*dy+0.0f;
const float dx33 =  + -3.02557  + 0.0262125 *lambda + -0.00028279 *lens_ipow(y, 2) + 0.278569 *x*dx + 16.1714 *lens_ipow(dx, 2) + 0.00117665 *lens_ipow(x, 2) + 17.5619 *lens_ipow(dy, 2)*lambda + -0.391177 *x*lens_ipow(dx, 3) + 174.387 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 3.98036 *x*dx*lens_ipow(dy, 2) + 0.0365468 *x*y*dx*dy + -18.7022 *lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 1.57263 *y*lens_ipow(dx, 2)*dy + 0.0221646 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 1.77456e-05 *lens_ipow(x, 3)*dx + -23.2769 *lens_ipow(dx, 4) + 0.000207444 *lens_ipow(x, 2)*y*dy + 8.99688 *lens_ipow(dy, 2)*lens_ipow(lambda, 6)+0.0f;
const float dx34 =  + 0.0262125 *dy + -0.000273248 *y + 5.85395 *lens_ipow(dy, 3) + -1.29969e-06 *lens_ipow(y, 3) + -12.4681 *lens_ipow(dy, 3)*lambda + 1.19833e-05 *lens_ipow(y, 3)*lens_ipow(lambda, 4) + 17.9938 *lens_ipow(dy, 3)*lens_ipow(lambda, 5)+0.0f;
const float dx40 =  + 0.000266756 *dx + -0.268464 *lens_ipow(dx, 3) + -4.71209e-05 *x*y*dy + -2.35063e-05 *lens_ipow(y, 2)*dx + -2.20321e-07 *x*lens_ipow(y, 2) + -0.007528 *x*lens_ipow(dx, 2) + -7.09292e-05 *lens_ipow(x, 2)*dx + -0.26844 *dx*lens_ipow(dy, 2) + -2.15613e-07 *lens_ipow(x, 3) + -0.00500763 *y*dx*dy + -0.00249737 *x*lens_ipow(dy, 2)+0.0f;
const float dx41 =  + 0.000259609 *dy + -0.267851 *lens_ipow(dy, 3) + -0.00249083 *y*lens_ipow(dx, 2) + -2.35604e-05 *lens_ipow(x, 2)*dy + -4.70126e-05 *x*y*dx + -2.20321e-07 *lens_ipow(x, 2)*y + -2.14836e-07 *lens_ipow(y, 3) + -0.268213 *lens_ipow(dx, 2)*dy + -0.00750498 *y*lens_ipow(dy, 2) + -0.00500763 *x*dx*dy + -7.06296e-05 *lens_ipow(y, 2)*dy+0.0f;
const float dx42 =  + 0.000266756 *x + 0.0343417 *dx + -29.3045 *lens_ipow(dx, 3) + -0.00249083 *lens_ipow(y, 2)*dx + -0.805391 *x*lens_ipow(dx, 2) + -29.3339 *dx*lens_ipow(dy, 2) + -2.35063e-05 *x*lens_ipow(y, 2) + -0.007528 *lens_ipow(x, 2)*dx + -0.536426 *y*dx*dy + -2.36431e-05 *lens_ipow(x, 3) + -0.26844 *x*lens_ipow(dy, 2) + -0.00500763 *x*y*dy+0.0f;
const float dx43 =  + 0.000259609 *y + 0.0336355 *dy + -0.803554 *y*lens_ipow(dy, 2) + -29.3339 *lens_ipow(dx, 2)*dy + -2.35604e-05 *lens_ipow(x, 2)*y + -29.2536 *lens_ipow(dy, 3) + -0.268213 *y*lens_ipow(dx, 2) + -0.00750498 *lens_ipow(y, 2)*dy + -0.536881 *x*dx*dy + -0.00500763 *x*y*dx + -0.00249737 *lens_ipow(x, 2)*dy + -2.35432e-05 *lens_ipow(y, 3)+0.0f;
const float dx44 =  + 3.76112  + -21.5935 *lambda + 49.3108 *lens_ipow(lambda, 2) + -51.7647 *lens_ipow(lambda, 3) + 20.7974 *lens_ipow(lambda, 4)+0.0f;