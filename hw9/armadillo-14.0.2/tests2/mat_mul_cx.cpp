// SPDX-License-Identifier: Apache-2.0
// 
// Copyright 2015 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2015 National ICT Australia (NICTA)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------


#include <armadillo>
#include "catch.hpp"

using namespace arma;


TEST_CASE("mat_mul_cx_1")
  {
  mat A = 
    "\
     0.061198   0.201990   0.019678  -0.493936  -0.126745   0.051408;\
     0.437242   0.058956  -0.149362  -0.045465   0.296153   0.035437;\
    -0.492474  -0.031309   0.314156   0.419733   0.068317  -0.454499;\
     0.336352   0.411541   0.458476  -0.393139  -0.135040   0.373833;\
     0.239585  -0.428913  -0.406953  -0.291020  -0.353768   0.258704;\
    ";
  
  cx_mat C = cx_mat(A,fliplr(A));
  
  cx_mat D = cx_mat(flipud(A),-fliplr(A));
  
     double re = 2.0;
  cx_double cx = cx_double(2.0,-3.0);
  
  
  cx_mat C_times_D_t = 
    "\
    (-0.185711,0.141986) (0.320782,-0.123588) (-6.93889e-18,-0.364555) (-0.320782,-0.123588) (0.185711,0.141986);\
    (0.0354121,0.18557) (-0.214015,0.406658) (-3.46945e-18,-0.596795) (0.214015,0.406658) (-0.0354121,0.18557);\
    (-0.226682,-0.699037) (-0.0995861,-0.534099) (2.77556e-17,1.41421) (0.0995861,-0.534099) (0.226682,-0.699037);\
    (-0.366865,-0.157988) (0.711264,0.107008) (0,-0.471402) (-0.711264,0.107008) (0.366865,-0.157988);\
    (0.561849,0.870633) (-0.0814947,0.151169) (-1.38778e-17,-1.03352) (0.0814947,0.151169) (-0.561849,0.870633);\
    ";
  
  cx_mat C_t_times_D = 
    "\
    (0.148843,-0.857543) (0.406412,-0.0389706) (0.415351,0.656975) (-0.449094,0.526547) (-0.114683,-0.11312) (-0.00283814,-0.867653);\
    (0.406412,-0.0244952) (-0.375592,-0.180565) (-0.368772,-0.0694664) (0.041254,-0.478571) (0.00880269,-0.412947) (0.123148,-0.11312);\
    (0.415351,0.610998) (-0.368772,-0.154831) (-0.715746,-0.432138) (0.2979,-0.996616) (0.374591,-0.478571) (0.260569,0.526547);\
    (-0.449094,0.464705) (0.041254,-0.0989421) (0.2979,-0.607187) (0.00221322,-0.432138) (-0.218553,-0.0694664) (-0.202333,0.656975);\
    (-0.114683,-0.0682625) (0.00880269,-0.128059) (0.374591,-0.0989421) (-0.218553,-0.154831) (-0.38423,-0.180565) (-0.0653194,-0.0389706);\
    (-0.00283814,-0.983136) (0.123148,-0.0682625) (0.260569,0.464705) (-0.202333,0.610998) (-0.0653194,-0.0244952) (-0.348327,-0.857543);\
    ";
  
  //
  
  cx_mat re_times_C_times_D_t = 
    "\
    (-0.371422,0.283972) (0.641564,-0.247176) (-1.38778e-17,-0.72911) (-0.641564,-0.247176) (0.371422,0.283972);\
    (0.0708241,0.37114) (-0.428029,0.813317) (-6.93889e-18,-1.19359) (0.428029,0.813317) (-0.0708241,0.37114);\
    (-0.453363,-1.39807) (-0.199172,-1.0682) (5.55112e-17,2.82841) (0.199172,-1.0682) (0.453363,-1.39807);\
    (-0.733729,-0.315977) (1.42253,0.214017) (0,-0.942804) (-1.42253,0.214017) (0.733729,-0.315977);\
    (1.1237,1.74127) (-0.162989,0.302339) (-2.77556e-17,-2.06704) (0.162989,0.302339) (-1.1237,1.74127);\
    ";
  
  cx_mat re_times_C_t_times_D = 
    "\
    (0.297685,-1.71509) (0.812823,-0.0779412) (0.830702,1.31395) (-0.898189,1.05309) (-0.229366,-0.22624) (-0.00567628,-1.73531);\
    (0.812823,-0.0489904) (-0.751184,-0.36113) (-0.737545,-0.138933) (0.0825079,-0.957143) (0.0176054,-0.825894) (0.246297,-0.22624);\
    (0.830702,1.222) (-0.737545,-0.309662) (-1.43149,-0.864277) (0.595799,-1.99323) (0.749183,-0.957143) (0.521138,1.05309);\
    (-0.898189,0.92941) (0.0825079,-0.197884) (0.595799,-1.21437) (0.00442644,-0.864277) (-0.437106,-0.138933) (-0.404666,1.31395);\
    (-0.229366,-0.136525) (0.0176054,-0.256119) (0.749183,-0.197884) (-0.437106,-0.309662) (-0.768459,-0.36113) (-0.130639,-0.0779412);\
    (-0.00567628,-1.96627) (0.246297,-0.136525) (0.521138,0.92941) (-0.404666,1.222) (-0.130639,-0.0489904) (-0.696654,-1.71509);\
    ";
  
  //
  
  cx_mat C_times_re_times_D_t = 
    "\
    (-0.371422,0.283972) (0.641564,-0.247176) (-1.38778e-17,-0.72911) (-0.641564,-0.247176) (0.371422,0.283972);\
    (0.0708241,0.37114) (-0.428029,0.813317) (-6.93889e-18,-1.19359) (0.428029,0.813317) (-0.0708241,0.37114);\
    (-0.453363,-1.39807) (-0.199172,-1.0682) (5.55112e-17,2.82841) (0.199172,-1.0682) (0.453363,-1.39807);\
    (-0.733729,-0.315977) (1.42253,0.214017) (0,-0.942804) (-1.42253,0.214017) (0.733729,-0.315977);\
    (1.1237,1.74127) (-0.162989,0.302339) (-2.77556e-17,-2.06704) (0.162989,0.302339) (-1.1237,1.74127);\
    ";
  
  cx_mat C_t_times_re_times_D = 
    "\
    (0.297685,-1.71509) (0.812823,-0.0779412) (0.830702,1.31395) (-0.898189,1.05309) (-0.229366,-0.22624) (-0.00567628,-1.73531);\
    (0.812823,-0.0489904) (-0.751184,-0.36113) (-0.737545,-0.138933) (0.0825079,-0.957143) (0.0176054,-0.825894) (0.246297,-0.22624);\
    (0.830702,1.222) (-0.737545,-0.309662) (-1.43149,-0.864277) (0.595799,-1.99323) (0.749183,-0.957143) (0.521138,1.05309);\
    (-0.898189,0.92941) (0.0825079,-0.197884) (0.595799,-1.21437) (0.00442644,-0.864277) (-0.437106,-0.138933) (-0.404666,1.31395);\
    (-0.229366,-0.136525) (0.0176054,-0.256119) (0.749183,-0.197884) (-0.437106,-0.309662) (-0.768459,-0.36113) (-0.130639,-0.0779412);\
    (-0.00567628,-1.96627) (0.246297,-0.136525) (0.521138,0.92941) (-0.404666,1.222) (-0.130639,-0.0489904) (-0.696654,-1.71509);\
    ";
  
  //
  
  cx_mat re_times_C_times_re_times_D_t = 
    "\
    (-0.742845,0.567944) (1.28313,-0.494352) (-2.77556e-17,-1.45822) (-1.28313,-0.494352) (0.742845,0.567944);\
    (0.141648,0.742279) (-0.856058,1.62663) (-1.38778e-17,-2.38718) (0.856058,1.62663) (-0.141648,0.742279);\
    (-0.906726,-2.79615) (-0.398345,-2.13639) (1.11022e-16,5.65683) (0.398345,-2.13639) (0.906726,-2.79615);\
    (-1.46746,-0.631953) (2.84506,0.428033) (0,-1.88561) (-2.84506,0.428033) (1.46746,-0.631953);\
    (2.2474,3.48253) (-0.325979,0.604678) (-5.55112e-17,-4.13407) (0.325979,0.604678) (-2.2474,3.48253);\
    ";
  
  cx_mat re_times_C_t_times_re_times_D = 
    "\
    (0.59537,-3.43017) (1.62565,-0.155882) (1.6614,2.6279) (-1.79638,2.10619) (-0.458732,-0.452481) (-0.0113526,-3.47061);\
    (1.62565,-0.0979807) (-1.50237,-0.722259) (-1.47509,-0.277865) (0.165016,-1.91429) (0.0352108,-1.65179) (0.492593,-0.452481);\
    (1.6614,2.44399) (-1.47509,-0.619323) (-2.86299,-1.72855) (1.1916,-3.98646) (1.49837,-1.91429) (1.04228,2.10619);\
    (-1.79638,1.85882) (0.165016,-0.395768) (1.1916,-2.42875) (0.00885288,-1.72855) (-0.874212,-0.277865) (-0.809332,2.6279);\
    (-0.458732,-0.27305) (0.0352108,-0.512237) (1.49837,-0.395768) (-0.874212,-0.619323) (-1.53692,-0.722259) (-0.261278,-0.155882);\
    (-0.0113526,-3.93254) (0.492593,-0.27305) (1.04228,1.85882) (-0.809332,2.44399) (-0.261278,-0.0979807) (-1.39331,-3.43017);\
    ";
  
  //
  
  cx_mat cx_times_C_times_D_t = 
    "\
    (0.0545359,0.841106) (0.2708,-1.20952) (-1.09366,-0.72911) (-1.01233,0.71517) (0.797381,-0.273161);\
    (0.627534,0.264904) (0.791946,1.45536) (-1.79039,-1.19359) (1.648,0.171273) (0.485885,0.477376);\
    (-2.55047,-0.718029) (-1.80147,-0.769439) (4.24262,2.82841) (-1.40312,-1.36696) (-1.64375,-2.07812);\
    (-1.20769,0.784617) (1.74355,-1.91978) (-1.41421,-0.942804) (-1.1015,2.34781) (0.259764,-1.41657);\
    (3.7356,0.0557187) (0.290519,0.546823) (-3.10056,-2.06704) (0.616498,0.0578546) (1.4882,3.42681);\
    ";
  
  cx_mat cx_times_C_t_times_D = 
    "\
    (-2.27494,-2.16161) (0.695911,-1.29718) (2.80163,0.0678966) (0.681454,2.40038) (-0.568727,0.117809) (-2.60864,-1.72679);\
    (0.739338,-1.26823) (-1.29288,0.765647) (-0.945944,0.967385) (-1.35321,-1.0809) (-1.22124,-0.852303) (-0.0930641,-0.595685);\
    (2.6637,-0.0240567) (-1.20204,0.796656) (-2.72791,1.28296) (-2.39405,-2.88693) (-0.686531,-2.08092) (2.10078,0.271388);\
    (0.495926,2.27669) (-0.214318,-0.321646) (-1.22576,-2.10807) (-1.29199,-0.870917) (-0.645505,0.516726) (1.56626,1.92095);\
    (-0.434154,0.207524) (-0.366573,-0.282527) (0.452357,-1.32166) (-0.901598,0.345997) (-1.31015,0.791559) (-0.247551,0.118017);\
    (-2.95508,-1.95776) (0.0415092,-0.50597) (1.91525,0.147703) (1.42833,1.82899) (-0.204124,0.146968) (-3.26928,-0.670106);\
    ";
  
  //
  
  cx_mat C_times_cx_times_D_t = 
    "\
    (0.0545359,0.841106) (0.2708,-1.20952) (-1.09366,-0.72911) (-1.01233,0.71517) (0.797381,-0.273161);\
    (0.627534,0.264904) (0.791946,1.45536) (-1.79039,-1.19359) (1.648,0.171273) (0.485885,0.477376);\
    (-2.55047,-0.718029) (-1.80147,-0.769439) (4.24262,2.82841) (-1.40312,-1.36696) (-1.64375,-2.07812);\
    (-1.20769,0.784617) (1.74355,-1.91978) (-1.41421,-0.942804) (-1.1015,2.34781) (0.259764,-1.41657);\
    (3.7356,0.0557187) (0.290519,0.546823) (-3.10056,-2.06704) (0.616498,0.0578546) (1.4882,3.42681);\
    ";
  
  cx_mat C_t_times_cx_times_D = 
    "\
    (-2.27494,-2.16161) (0.695911,-1.29718) (2.80163,0.0678966) (0.681454,2.40038) (-0.568727,0.117809) (-2.60864,-1.72679);\
    (0.739338,-1.26823) (-1.29288,0.765647) (-0.945944,0.967385) (-1.35321,-1.0809) (-1.22124,-0.852303) (-0.0930641,-0.595685);\
    (2.6637,-0.0240567) (-1.20204,0.796656) (-2.72791,1.28296) (-2.39405,-2.88693) (-0.686531,-2.08092) (2.10078,0.271388);\
    (0.495926,2.27669) (-0.214318,-0.321646) (-1.22576,-2.10807) (-1.29199,-0.870917) (-0.645505,0.516726) (1.56626,1.92095);\
    (-0.434154,0.207524) (-0.366573,-0.282527) (0.452357,-1.32166) (-0.901598,0.345997) (-1.31015,0.791559) (-0.247551,0.118017);\
    (-2.95508,-1.95776) (0.0415092,-0.50597) (1.91525,0.147703) (1.42833,1.82899) (-0.204124,0.146968) (-3.26928,-0.670106);\
    ";
  
  //
  
  cx_mat cx_times_C_times_cx_times_D_t = 
    "\
    (2.63239,1.5186) (-3.08696,-3.23144) (-4.37466,1.82277) (0.120855,4.46732) (0.775277,-2.93847);\
    (2.04978,-1.35279) (5.94997,0.534883) (-7.16154,2.98398) (3.80983,-4.60147) (2.4039,-0.502904);\
    (-7.25503,6.21536) (-5.91125,3.86553) (16.9705,-7.07103) (-6.90711,1.47546) (-9.52185,0.775005);\
    (-0.0615364,5.19232) (-2.27222,-9.07021) (-5.65682,2.35701) (4.84042,8.00013) (-3.73018,-3.61243);\
    (7.63835,-11.0954) (2.22151,0.22209) (-12.4022,5.16759) (1.40656,-1.73378) (13.2568,2.38902);\
    ";
  
  cx_mat cx_times_C_t_times_cx_times_D = 
    "\
    (-11.0347,2.5016) (-2.49971,-4.68209) (5.80694,-8.26908) (8.56404,2.7564) (-0.784027,1.9418) (-10.3976,4.37232);\
    (-2.326,-4.75446) (-0.288817,5.40993) (1.01027,4.7726) (-5.94913,1.89781) (-4.99938,1.9591) (-1.97318,-0.912178);\
    (5.25522,-8.0392) (-0.0141081,5.19942) (-1.60693,10.7496) (-13.4489,1.40828) (-7.61581,-2.10224) (5.01572,-5.75956);\
    (7.82193,3.06561) (-1.39358,-0.000336933) (-8.77574,-0.538863) (-5.19673,2.13413) (0.259168,2.96997) (8.89536,-0.856878);\
    (-0.245734,1.71751) (-1.58073,0.534664) (-3.06026,-4.00039) (-0.765206,3.39679) (-0.24563,5.51358) (-0.14105,0.978686);\
    (-11.7834,4.94974) (-1.43489,-1.13647) (4.27362,-5.45035) (8.34364,-0.626995) (0.0326548,0.906309) (-8.54888,8.46764);\
    ";
  
  
  
  REQUIRE( accu(abs( C*D.t() - C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t()*D - C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  //
  
  REQUIRE( accu(abs( re*C*D.t() - re_times_C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( re*C.t()*D - re_times_C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( C*re*D.t() - C_times_re_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t()*re*D - C_t_times_re_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( re*C*re*D.t() - re_times_C_times_re_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( re*C.t()*re*D - re_times_C_t_times_re_times_D )) == Approx(0.0).margin(0.00010) );
  
  //
  
  REQUIRE( accu(abs( (re*C)*D.t() - re_times_C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( (re*C.t())*D - re_times_C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( C*(re*D.t()) - C_times_re_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t()*(re*D) - C_t_times_re_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( (re*C)*(re*D.t()) - re_times_C_times_re_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( (re*C.t())*(re*D) - re_times_C_t_times_re_times_D )) == Approx(0.0).margin(0.00010) );


  REQUIRE( accu(abs( C*D.t().eval() - C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t().eval()*D - C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  //
  
  REQUIRE( accu(abs( re*C*D.t().eval() - re_times_C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( re*C.t().eval()*D - re_times_C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( C*re*D.t().eval() - C_times_re_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t().eval()*re*D - C_t_times_re_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( re*C*re*D.t().eval() - re_times_C_times_re_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( re*C.t().eval()*re*D - re_times_C_t_times_re_times_D )) == Approx(0.0).margin(0.00010) );
  
  //
  
  REQUIRE( accu(abs( (re*C)*(D.t().eval()) - re_times_C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( (re*C.t()).eval()*D - re_times_C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( C*(re*D.t()).eval() - C_times_re_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t().eval()*(re*D) - C_t_times_re_times_D )) == Approx(0.0).margin(0.00005) );
  
  REQUIRE( accu(abs( (re*C)*(re*D.t()).eval() - re_times_C_times_re_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( (re*C.t()).eval()*(re*D) - re_times_C_t_times_re_times_D )) == Approx(0.0).margin(0.00010) );


  //
  
  REQUIRE( accu(abs( cx*C*D.t() - cx_times_C_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( cx*C.t()*D - cx_times_C_t_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( C*cx*D.t() - C_times_cx_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( C.t()*cx*D - C_t_times_cx_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( cx*C*cx*D.t() - cx_times_C_times_cx_times_D_t )) == Approx(0.0).margin(0.00030) );
  REQUIRE( accu(abs( cx*C.t()*cx*D - cx_times_C_t_times_cx_times_D )) == Approx(0.0).margin(0.00030) );
  
  //
  
  REQUIRE( accu(abs( (cx*C)*D.t() - cx_times_C_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( (cx*C.t())*D - cx_times_C_t_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( C*(cx*D.t()) - C_times_cx_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( C.t()*(cx*D) - C_t_times_cx_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( (cx*C)*(cx*D.t()) - cx_times_C_times_cx_times_D_t )) == Approx(0.0).margin(0.00030) );
  REQUIRE( accu(abs( (cx*C.t())*(cx*D) - cx_times_C_t_times_cx_times_D )) == Approx(0.0).margin(0.00030) );


  REQUIRE( accu(abs( C*D.t().eval() - C_times_D_t )) == Approx(0.0).margin(0.00005) );
  REQUIRE( accu(abs( C.t().eval()*D - C_t_times_D )) == Approx(0.0).margin(0.00005) );
  
  //
  
  REQUIRE( accu(abs( cx*C*D.t().eval() - cx_times_C_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( cx*C.t().eval()*D - cx_times_C_t_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( C*cx*D.t().eval() - C_times_cx_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( C.t().eval()*cx*D - C_t_times_cx_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( cx*C*cx*D.t().eval() - cx_times_C_times_cx_times_D_t )) == Approx(0.0).margin(0.00030) );
  REQUIRE( accu(abs( cx*C.t().eval()*cx*D - cx_times_C_t_times_cx_times_D )) == Approx(0.0).margin(0.00030) );
  
  //
  
  REQUIRE( accu(abs( (cx*C)*(D.t().eval()) - cx_times_C_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( (cx*C.t()).eval()*D   - cx_times_C_t_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( C*(cx*D.t()).eval() - C_times_cx_times_D_t )) == Approx(0.0).margin(0.00010) );
  REQUIRE( accu(abs( C.t().eval()*(cx*D) - C_t_times_cx_times_D )) == Approx(0.0).margin(0.00010) );
  
  REQUIRE( accu(abs( (cx*C)*(cx*D.t()).eval() - cx_times_C_times_cx_times_D_t )) == Approx(0.0).margin(0.00030) );
  REQUIRE( accu(abs( (cx*C.t()).eval()*(cx*D) - cx_times_C_t_times_cx_times_D )) == Approx(0.0).margin(0.00030) );
  }



