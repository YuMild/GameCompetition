#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0 /Emain /D __INST__=40 /Fh
//    ShaderHeader/ad_model_unlit_ps.h Shader/ad_model_unlit_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer PS_ConstanBuffer
// {
//
//   float4 fLightDirection;            // Offset:    0 Size:    16 [unused]
//   float4 fLightColor;                // Offset:   16 Size:    16 [unused]
//   float4 fLightAmbient;              // Offset:   32 Size:    16 [unused]
//   float4 fFlipbookParameter;         // Offset:   48 Size:    16
//   float4 fUVDistortionParameter;     // Offset:   64 Size:    16
//   float4 fBlendTextureParameter;     // Offset:   80 Size:    16
//   float4 fCameraFrontDirection;      // Offset:   96 Size:    16
//   float4 fFalloffParameter;          // Offset:  112 Size:    16
//   float4 fFalloffBeginColor;         // Offset:  128 Size:    16
//   float4 fFalloffEndColor;           // Offset:  144 Size:    16
//   float4 fEmissiveScaling;           // Offset:  160 Size:    16
//   float4 fEdgeColor;                 // Offset:  176 Size:    16
//   float4 fEdgeParameter;             // Offset:  192 Size:    16
//   float4 softParticleParam;          // Offset:  208 Size:    16
//   float4 reconstructionParam1;       // Offset:  224 Size:    16
//   float4 reconstructionParam2;       // Offset:  240 Size:    16
//   float4 mUVInversedBack;            // Offset:  256 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// sampler_colorTex                  sampler      NA          NA    0        1
// sampler_alphaTex                  sampler      NA          NA    1        1
// sampler_uvDistortionTex           sampler      NA          NA    2        1
// sampler_blendTex                  sampler      NA          NA    3        1
// sampler_blendAlphaTex             sampler      NA          NA    4        1
// sampler_blendUVDistortionTex      sampler      NA          NA    5        1
// sampler_depthTex                  sampler      NA          NA    6        1
// _colorTex                         texture  float4          2d    0        1
// _alphaTex                         texture  float4          2d    1        1
// _uvDistortionTex                  texture  float4          2d    2        1
// _blendTex                         texture  float4          2d    3        1
// _blendAlphaTex                    texture  float4          2d    4        1
// _blendUVDistortionTex             texture  float4          2d    5        1
// _depthTex                         texture  float4          2d    6        1
// PS_ConstanBuffer                  cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// COLOR                    0   xyzw        1     NONE  float   xyzw
// TEXCOORD                 0   xyzw        2     NONE  float   xyzw
// TEXCOORD                 1   xyz         3     NONE  float   xyz 
// TEXCOORD                 4   xyzw        4     NONE  float   xyzw
// TEXCOORD                 5   xyzw        5     NONE  float   xyzw
// TEXCOORD                 6   xyzw        6     NONE  float   xyzw
// TEXCOORD                 7   xyzw        7     NONE  float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
ps_4_0
dcl_constantbuffer cb0[17], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_sampler s2, mode_default
dcl_sampler s3, mode_default
dcl_sampler s4, mode_default
dcl_sampler s5, mode_default
dcl_sampler s6, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_resource_texture2d (float,float,float,float) t3
dcl_resource_texture2d (float,float,float,float) t4
dcl_resource_texture2d (float,float,float,float) t5
dcl_resource_texture2d (float,float,float,float) t6
dcl_input_ps linear centroid v1.xyzw
dcl_input_ps linear centroid v2.xyzw
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xyzw
dcl_input_ps linear v5.xyzw
dcl_input_ps linear v6.xyzw
dcl_input_ps linear v7.xyzw
dcl_output o0.xyzw
dcl_temps 7
sample r0.xyzw, v4.zwzz, t2.xyzw, s2
mad r0.xy, r0.xyxx, l(2.000000, 2.000000, 0.000000, 0.000000), l(-1.000000, -1.000000, 0.000000, 0.000000)
mad r0.z, -r0.y, cb0[4].w, cb0[4].z
mad r0.yw, r0.xxxz, cb0[4].xxxx, v2.xxxy
sample r1.xyzw, r0.ywyy, t0.xyzw, s0
mul r1.xyzw, r1.xyzw, v1.xyzw
lt r0.y, l(0.000000), cb0[3].x
if_nz r0.y
  mad r0.yw, r0.xxxz, cb0[4].xxxx, v6.zzzw
  sample r2.xyzw, r0.ywyy, t0.xyzw, s0
  eq r0.y, cb0[3].y, l(1.000000)
  mad r2.xyzw, r2.xyzw, v1.xyzw, -r1.xyzw
  mad r2.xyzw, v2.zzzz, r2.xyzw, r1.xyzw
  movc r1.xyzw, r0.yyyy, r2.xyzw, r1.xyzw
endif 
mad r0.xy, r0.xzxx, cb0[4].xxxx, v4.xyxx
sample r0.xyzw, r0.xyxx, t1.xyzw, s1
mul r0.x, r0.w, r0.x
mul r0.w, r0.x, r1.w
sample r2.xyzw, v5.zwzz, t5.xyzw, s5
mad r2.xy, r2.xyxx, l(2.000000, 2.000000, 0.000000, 0.000000), l(-1.000000, -1.000000, 0.000000, 0.000000)
mad r2.z, -r2.y, cb0[4].w, cb0[4].z
mad r2.yw, r2.xxxz, cb0[4].yyyy, v6.xxxy
sample r3.xyzw, r2.ywyy, t3.xyzw, s3
mad r2.xy, r2.xzxx, cb0[4].yyyy, v5.xyxx
sample r2.xyzw, r2.xyxx, t4.xyzw, s4
mul r1.w, r2.w, r2.x
mul r2.x, r1.w, r3.w
mul r2.yzw, r3.xxyz, r2.xxxx
mad r1.w, -r3.w, r1.w, l(1.000000)
mad r4.xyz, r1.wwww, r1.xyzx, r2.yzwy
mad r5.xyz, r2.xxxx, r3.xyzx, r1.xyzx
mad r3.xyz, -r2.xxxx, r3.xyzx, r1.xyzx
eq r6.xyzw, cb0[5].xxxx, l(0.000000, 1.000000, 2.000000, 3.000000)
mul r2.xyz, r1.xyzx, r2.yzwy
movc r1.xyz, r6.wwww, r2.xyzx, r1.xyzx
movc r1.xyz, r6.zzzz, r3.xyzx, r1.xyzx
movc r1.xyz, r6.yyyy, r5.xyzx, r1.xyzx
movc r0.xyz, r6.xxxx, r4.xyzx, r1.xyzx
dp3 r1.x, -cb0[6].xyzx, -cb0[6].xyzx
rsq r1.x, r1.x
mul r1.xyz, r1.xxxx, -cb0[6].xyzx
dp3 r1.w, v3.xyzx, v3.xyzx
rsq r1.w, r1.w
mul r2.xyz, r1.wwww, v3.xyzx
dp3_sat r1.x, r1.xyzx, r2.xyzx
log r1.x, r1.x
mul r1.x, r1.x, cb0[7].z
exp r1.x, r1.x
add r2.xyzw, cb0[8].xyzw, -cb0[9].xyzw
mad r1.xyzw, r1.xxxx, r2.xyzw, cb0[9].xyzw
add r2.xyz, r0.xyzx, r1.xyzx
add r3.xyz, r0.xyzx, -r1.xyzx
eq r4.xyzw, cb0[7].xyyy, l(1.000000, 0.000000, 1.000000, 2.000000)
mul r1.xyz, r0.xyzx, r1.xyzx
movc r1.xyz, r4.wwww, r1.xyzx, r0.xyzx
movc r1.xyz, r4.zzzz, r3.xyzx, r1.xyzx
movc r2.xyz, r4.yyyy, r2.xyzx, r1.xyzx
mul r2.w, r0.w, r1.w
movc r0.xyzw, r4.xxxx, r2.xyzw, r0.xyzw
ne r1.x, cb0[13].w, l(0.000000)
if_nz r1.x
  div r1.yzw, v7.xxyz, v7.wwww
  add r1.yz, r1.yyzy, l(0.000000, 1.000000, 1.000000, 0.000000)
  mul r2.x, r1.y, l(0.500000)
  mad r1.y, -r1.z, l(0.500000), l(1.000000)
  mad r2.z, cb0[16].y, r1.y, cb0[16].x
  sample r2.xyzw, r2.xzxx, t6.xyzw, s6
  mad r1.x, r2.x, cb0[14].x, cb0[14].y
  mad r1.yz, r1.xxwx, cb0[15].wwww, -cb0[15].yyyy
  mad r1.xw, -r1.xxxw, cb0[15].zzzz, cb0[15].xxxx
  div r1.xy, r1.yzyy, r1.xwxx
  add r1.x, -r1.x, r1.y
  add r1.y, -r1.y, -cb0[13].z
  div r1.xy, r1.xyxx, cb0[13].xyxx
  min_sat r1.x, r1.y, r1.x
  mul r0.w, r0.w, r1.x
endif 
max r1.x, v2.w, l(0.000000)
ge r1.x, r1.x, r0.w
discard r1.x
mul r1.xyz, cb0[11].xyzx, cb0[12].yyyy
add r1.w, r0.w, -v2.w
add r1.w, r1.w, -cb0[12].x
round_pi r1.w, r1.w
mad r2.xyz, r0.xyzx, cb0[10].xxxx, -r1.xyzx
mad r0.xyz, r1.wwww, r2.xyzx, r1.xyzx
mov o0.xyzw, r0.xyzw
ret 
// Approximately 89 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67, 253,  38, 
     77, 232, 204, 173,   9,  36, 
    202,  86, 245, 204, 200, 234, 
    117, 100,   1,   0,   0,   0, 
    192,  20,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     88,   6,   0,   0,  68,   7, 
      0,   0, 120,   7,   0,   0, 
     68,  20,   0,   0,  82,  68, 
     69,  70,  28,   6,   0,   0, 
      1,   0,   0,   0, 252,   2, 
      0,   0,  15,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    234,   5,   0,   0, 252,   1, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   2,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  30,   2,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  54,   2, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     71,   2,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  93,   2,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 122,   2, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    139,   2,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 149,   2,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 159,   2, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    176,   2,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   3,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 186,   2,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   4,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 201,   2, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      5,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    223,   2,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   6,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 233,   2,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 115,  97, 
    109, 112, 108, 101, 114,  95, 
     99, 111, 108, 111, 114,  84, 
    101, 120,   0, 115,  97, 109, 
    112, 108, 101, 114,  95,  97, 
    108, 112, 104,  97,  84, 101, 
    120,   0, 115,  97, 109, 112, 
    108, 101, 114,  95, 117, 118, 
     68, 105, 115, 116, 111, 114, 
    116, 105, 111, 110,  84, 101, 
    120,   0, 115,  97, 109, 112, 
    108, 101, 114,  95,  98, 108, 
    101, 110, 100,  84, 101, 120, 
      0, 115,  97, 109, 112, 108, 
    101, 114,  95,  98, 108, 101, 
    110, 100,  65, 108, 112, 104, 
     97,  84, 101, 120,   0, 115, 
     97, 109, 112, 108, 101, 114, 
     95,  98, 108, 101, 110, 100, 
     85,  86,  68, 105, 115, 116, 
    111, 114, 116, 105, 111, 110, 
     84, 101, 120,   0, 115,  97, 
    109, 112, 108, 101, 114,  95, 
    100, 101, 112, 116, 104,  84, 
    101, 120,   0,  95,  99, 111, 
    108, 111, 114,  84, 101, 120, 
      0,  95,  97, 108, 112, 104, 
     97,  84, 101, 120,   0,  95, 
    117, 118,  68, 105, 115, 116, 
    111, 114, 116, 105, 111, 110, 
     84, 101, 120,   0,  95,  98, 
    108, 101, 110, 100,  84, 101, 
    120,   0,  95,  98, 108, 101, 
    110, 100,  65, 108, 112, 104, 
     97,  84, 101, 120,   0,  95, 
     98, 108, 101, 110, 100,  85, 
     86,  68, 105, 115, 116, 111, 
    114, 116, 105, 111, 110,  84, 
    101, 120,   0,  95, 100, 101, 
    112, 116, 104,  84, 101, 120, 
      0,  80,  83,  95,  67, 111, 
    110, 115, 116,  97, 110,  66, 
    117, 102, 102, 101, 114,   0, 
    171, 171, 233,   2,   0,   0, 
     17,   0,   0,   0,  20,   3, 
      0,   0,  16,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 172,   4,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 204,   4,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 216,   4,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 230,   4,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 249,   4,   0,   0, 
     64,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  16,   5,   0,   0, 
     80,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  39,   5,   0,   0, 
     96,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  61,   5,   0,   0, 
    112,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  79,   5,   0,   0, 
    128,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  98,   5,   0,   0, 
    144,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 115,   5,   0,   0, 
    160,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 132,   5,   0,   0, 
    176,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 143,   5,   0,   0, 
    192,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 158,   5,   0,   0, 
    208,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 176,   5,   0,   0, 
    224,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 197,   5,   0,   0, 
    240,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 218,   5,   0,   0, 
      0,   1,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   4,   0,   0,   0,   0, 
      0,   0, 102,  76, 105, 103, 
    104, 116,  68, 105, 114, 101, 
     99, 116, 105, 111, 110,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 102,  76, 
    105, 103, 104, 116,  67, 111, 
    108, 111, 114,   0, 102,  76, 
    105, 103, 104, 116,  65, 109, 
     98, 105, 101, 110, 116,   0, 
    102,  70, 108, 105, 112,  98, 
    111, 111, 107,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
      0, 102,  85,  86,  68, 105, 
    115, 116, 111, 114, 116, 105, 
    111, 110,  80,  97, 114,  97, 
    109, 101, 116, 101, 114,   0, 
    102,  66, 108, 101, 110, 100, 
     84, 101, 120, 116, 117, 114, 
    101,  80,  97, 114,  97, 109, 
    101, 116, 101, 114,   0, 102, 
     67,  97, 109, 101, 114,  97, 
     70, 114, 111, 110, 116,  68, 
    105, 114, 101,  99, 116, 105, 
    111, 110,   0, 102,  70,  97, 
    108, 108, 111, 102, 102,  80, 
     97, 114,  97, 109, 101, 116, 
    101, 114,   0, 102,  70,  97, 
    108, 108, 111, 102, 102,  66, 
    101, 103, 105, 110,  67, 111, 
    108, 111, 114,   0, 102,  70, 
     97, 108, 108, 111, 102, 102, 
     69, 110, 100,  67, 111, 108, 
    111, 114,   0, 102,  69, 109, 
    105, 115, 115, 105, 118, 101, 
     83,  99,  97, 108, 105, 110, 
    103,   0, 102,  69, 100, 103, 
    101,  67, 111, 108, 111, 114, 
      0, 102,  69, 100, 103, 101, 
     80,  97, 114,  97, 109, 101, 
    116, 101, 114,   0, 115, 111, 
    102, 116,  80,  97, 114, 116, 
    105,  99, 108, 101,  80,  97, 
    114,  97, 109,   0, 114, 101, 
     99, 111, 110, 115, 116, 114, 
    117,  99, 116, 105, 111, 110, 
     80,  97, 114,  97, 109,  49, 
      0, 114, 101,  99, 111, 110, 
    115, 116, 114, 117,  99, 116, 
    105, 111, 110,  80,  97, 114, 
     97, 109,  50,   0, 109,  85, 
     86,  73, 110, 118, 101, 114, 
    115, 101, 100,  66,  97,  99, 
    107,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171,  73,  83, 
     71,  78, 228,   0,   0,   0, 
      8,   0,   0,   0,   8,   0, 
      0,   0, 200,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 212,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   7, 
      0,   0, 218,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      6,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      7,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0,  15,  15, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  67,  79,  76,  79, 
     82,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     68,  82, 196,  12,   0,   0, 
     64,   0,   0,   0,  49,   3, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  17,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   1,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   3,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   4,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   5,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   6,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      1,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   2,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   3,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      4,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   5,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   6,   0,   0,   0, 
     85,  85,   0,   0,  98,  24, 
      0,   3, 242,  16,  16,   0, 
      1,   0,   0,   0,  98,  24, 
      0,   3, 242,  16,  16,   0, 
      2,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      3,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      4,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      5,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      6,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      7,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   7,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
    230,  26,  16,   0,   4,   0, 
      0,   0,  70, 126,  16,   0, 
      2,   0,   0,   0,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  15,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  12,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     58, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     42, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     50,   0,   0,  10, 162,   0, 
     16,   0,   0,   0,   0,   0, 
      6,   8,  16,   0,   0,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   6,  20,  16,   0, 
      2,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0, 214,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  30,  16,   0,   1,   0, 
      0,   0,  49,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  31,   0, 
      4,   3,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 162,   0,  16,   0, 
      0,   0,   0,   0,   6,   8, 
     16,   0,   0,   0,   0,   0, 
      6, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
    166,  30,  16,   0,   6,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 214,   5,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  24,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  30,  16,   0,   1,   0, 
      0,   0,  70,  14,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 166,  26,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  55,   0,   0,   9, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  21,   0,   0,   1, 
     50,   0,   0,  10,  50,   0, 
     16,   0,   0,   0,   0,   0, 
    134,   0,  16,   0,   0,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,  70,  16,  16,   0, 
      4,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,   0,  96,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    230,  26,  16,   0,   5,   0, 
      0,   0,  70, 126,  16,   0, 
      5,   0,   0,   0,   0,  96, 
     16,   0,   5,   0,   0,   0, 
     50,   0,   0,  15,  50,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   0,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  12,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
     58, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     42, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     50,   0,   0,  10, 162,   0, 
     16,   0,   2,   0,   0,   0, 
      6,   8,  16,   0,   2,   0, 
      0,   0,  86, 133,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   6,  20,  16,   0, 
      6,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      3,   0,   0,   0, 214,   5, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   3,   0, 
      0,   0,   0,  96,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  10,  50,   0,  16,   0, 
      2,   0,   0,   0, 134,   0, 
     16,   0,   2,   0,   0,   0, 
     86, 133,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     70,  16,  16,   0,   5,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,   0,  16,   0, 
      2,   0,   0,   0,  70, 126, 
     16,   0,   4,   0,   0,   0, 
      0,  96,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      2,   0,   0,   0,   6,   9, 
     16,   0,   3,   0,   0,   0, 
      6,   0,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16, 128, 
     65,   0,   0,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   4,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0, 150,   7, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   5,   0,   0,   0, 
      6,   0,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
      6,   0,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  24,   0, 
      0,  11, 242,   0,  16,   0, 
      6,   0,   0,   0,   6, 128, 
     32,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,  64,   0,   0,  64,  64, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0, 150,   7,  16,   0, 
      2,   0,   0,   0,  55,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0, 246,  15, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  55,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0, 166,  10, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  55,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  55,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,  11,  18,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,  70, 130,  32, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     68,   0,   0,   5,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      3,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     68,   0,   0,   5, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   2,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     16,  32,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  47,   0, 
      0,   5,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   8,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0,  25,   0,   0,   5, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  70, 142, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   9,   0,   0,   0, 
      0,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   8, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     24,   0,   0,  11, 242,   0, 
     16,   0,   4,   0,   0,   0, 
     70, 133,  32,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  63,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,  64,  56,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    246,  15,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    166,  10,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     86,   5,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  55,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  57,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  58, 128, 
     32,   0,   0,   0,   0,   0, 
     13,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   4,   3,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     14,   0,   0,   7, 226,   0, 
     16,   0,   1,   0,   0,   0, 
      6,  25,  16,   0,   7,   0, 
      0,   0, 246,  31,  16,   0, 
      7,   0,   0,   0,   0,   0, 
      0,  10,  98,   0,  16,   0, 
      1,   0,   0,   0,  86,   6, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     50,   0,   0,  10,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     42,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,  11,  66,   0,  16,   0, 
      2,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    134,   0,  16,   0,   2,   0, 
      0,   0,  70, 126,  16,   0, 
      6,   0,   0,   0,   0,  96, 
     16,   0,   6,   0,   0,   0, 
     50,   0,   0,  11,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   0,  50,   0,   0,  12, 
     98,   0,  16,   0,   1,   0, 
      0,   0,   6,   3,  16,   0, 
      1,   0,   0,   0, 246, 143, 
     32,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  86, 133, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  50,   0,   0,  12, 
    146,   0,  16,   0,   1,   0, 
      0,   0,   6,  12,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0, 166, 138,  32,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  14,   0,   0,   7, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 150,   5,  16,   0, 
      1,   0,   0,   0, 198,   0, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   8,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,  10, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  42, 128,  32, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  13,   0,   0,   0, 
     14,   0,   0,   8,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0,  70, 128,  32,   0, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  51,  32,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  21,   0, 
      0,   1,  52,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  58,  16,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     29,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  10,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
     11,   0,   0,   0,  86, 133, 
     32,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   8, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     58,  16,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   9, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  10, 128,  32, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
     66,   0,   0,   5, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  11, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,   6, 128, 
     32,   0,   0,   0,   0,   0, 
     10,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     89,   0,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  42,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,   9,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};
