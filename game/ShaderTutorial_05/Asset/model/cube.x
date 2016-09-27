xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 84;
 0.43000;-0.50000;0.43000;,
 -0.43000;-0.50000;0.43000;,
 -0.43000;-0.50000;-0.43000;,
 0.43000;-0.50000;-0.43000;,
 -0.43000;0.50000;-0.43000;,
 -0.43000;0.50000;0.43000;,
 0.43000;0.50000;0.43000;,
 0.43000;0.50000;-0.43000;,
 -0.43000;0.43000;0.50000;,
 -0.43000;-0.43000;0.50000;,
 0.43000;-0.43000;0.50000;,
 0.43000;0.43000;0.50000;,
 0.50000;0.43000;0.43000;,
 0.50000;-0.43000;0.43000;,
 0.50000;-0.43000;-0.43000;,
 0.50000;0.43000;-0.43000;,
 0.43000;0.43000;-0.50000;,
 0.43000;-0.43000;-0.50000;,
 -0.43000;-0.43000;-0.50000;,
 -0.43000;0.43000;-0.50000;,
 -0.50000;0.43000;-0.43000;,
 -0.50000;-0.43000;-0.43000;,
 -0.50000;-0.43000;0.43000;,
 -0.50000;0.43000;0.43000;,
 -0.43000;-0.43000;0.50000;,
 -0.50000;-0.43000;0.43000;,
 -0.43000;-0.50000;0.43000;,
 0.43000;-0.50000;0.43000;,
 0.50000;-0.43000;0.43000;,
 0.43000;-0.43000;0.50000;,
 -0.50000;-0.43000;-0.43000;,
 -0.43000;-0.43000;-0.50000;,
 -0.43000;-0.50000;-0.43000;,
 0.43000;-0.50000;-0.43000;,
 0.43000;-0.43000;-0.50000;,
 0.50000;-0.43000;-0.43000;,
 -0.43000;0.43000;0.50000;,
 -0.43000;0.50000;0.43000;,
 -0.50000;0.43000;0.43000;,
 0.50000;0.43000;0.43000;,
 0.43000;0.50000;0.43000;,
 0.43000;0.43000;0.50000;,
 -0.50000;0.43000;-0.43000;,
 -0.43000;0.50000;-0.43000;,
 -0.43000;0.43000;-0.50000;,
 0.43000;0.43000;-0.50000;,
 0.43000;0.50000;-0.43000;,
 0.50000;0.43000;-0.43000;,
 -0.43000;-0.50000;-0.43000;,
 -0.43000;-0.50000;0.43000;,
 -0.50000;-0.43000;0.43000;,
 -0.50000;-0.43000;-0.43000;,
 0.43000;-0.50000;-0.43000;,
 -0.43000;-0.50000;-0.43000;,
 -0.43000;-0.43000;-0.50000;,
 0.43000;-0.43000;-0.50000;,
 0.43000;-0.50000;0.43000;,
 0.43000;-0.50000;-0.43000;,
 0.50000;-0.43000;-0.43000;,
 0.50000;-0.43000;0.43000;,
 -0.43000;-0.50000;0.43000;,
 0.43000;-0.50000;0.43000;,
 0.43000;-0.43000;0.50000;,
 -0.43000;-0.43000;0.50000;,
 -0.43000;0.43000;0.50000;,
 0.50000;0.43000;0.43000;,
 0.43000;0.43000;-0.50000;,
 -0.50000;0.43000;-0.43000;,
 0.43000;0.43000;0.50000;,
 0.43000;-0.43000;0.50000;,
 0.50000;-0.43000;0.43000;,
 0.50000;0.43000;0.43000;,
 -0.43000;-0.43000;0.50000;,
 -0.43000;0.43000;0.50000;,
 -0.50000;0.43000;0.43000;,
 -0.50000;-0.43000;0.43000;,
 0.50000;0.43000;-0.43000;,
 0.50000;-0.43000;-0.43000;,
 0.43000;-0.43000;-0.50000;,
 0.43000;0.43000;-0.50000;,
 -0.43000;0.43000;-0.50000;,
 -0.43000;-0.43000;-0.50000;,
 -0.50000;-0.43000;-0.43000;,
 -0.50000;0.43000;-0.43000;;
 
 26;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 3;24,25,26;,
 3;27,28,29;,
 3;30,31,32;,
 3;33,34,35;,
 3;36,37,38;,
 3;39,40,41;,
 3;42,43,44;,
 3;45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;6,5,64,41;,
 4;7,6,65,47;,
 4;4,7,66,44;,
 4;5,4,67,38;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;;
 
 MeshMaterialList {
  3;
  26;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Cube earth.tga";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Cube grass.tga";
   }
  }
 }
 MeshNormals {
  24;
  0.367001;-0.854763;0.367001;,
  -0.367001;-0.854763;0.367001;,
  -0.367001;-0.854763;-0.367001;,
  0.367001;-0.854763;-0.367001;,
  -0.367001;0.854763;-0.367001;,
  -0.367001;0.854763;0.367001;,
  0.367001;0.854763;0.367001;,
  0.367001;0.854763;-0.367001;,
  -0.367001;0.367001;0.854763;,
  -0.367001;-0.367001;0.854763;,
  0.367001;-0.367001;0.854763;,
  0.367001;0.367001;0.854763;,
  0.854763;0.367001;0.367001;,
  0.854763;-0.367001;0.367001;,
  0.854763;-0.367001;-0.367001;,
  0.854763;0.367001;-0.367001;,
  0.367001;0.367001;-0.854763;,
  0.367001;-0.367001;-0.854763;,
  -0.367001;-0.367001;-0.854763;,
  -0.367001;0.367001;-0.854763;,
  -0.854763;0.367001;-0.367001;,
  -0.854763;-0.367001;-0.367001;,
  -0.854763;-0.367001;0.367001;,
  -0.854763;0.367001;0.367001;;
  26;
  4;0,1,2,3;,
  4;4,5,6,7;,
  4;8,9,10,11;,
  4;12,13,14,15;,
  4;16,17,18,19;,
  4;20,21,22,23;,
  3;9,22,1;,
  3;0,13,10;,
  3;21,18,2;,
  3;3,17,14;,
  3;8,5,23;,
  3;12,6,11;,
  3;20,4,19;,
  3;16,7,15;,
  4;2,1,22,21;,
  4;3,2,18,17;,
  4;0,3,14,13;,
  4;1,0,10,9;,
  4;6,5,8,11;,
  4;7,6,12,15;,
  4;4,7,16,19;,
  4;5,4,20,23;,
  4;11,10,13,12;,
  4;9,8,23,22;,
  4;15,14,17,16;,
  4;19,18,21,20;;
 }
 MeshTextureCoords {
  84;
  0.300848;0.496681;,
  0.298639;0.825303;,
  0.676930;0.827222;,
  0.679139;0.498600;,
  0.155800;0.266000;,
  0.361300;0.268900;,
  0.364000;0.063500;,
  0.158700;0.060600;,
  0.007596;0.026181;,
  0.019423;0.895602;,
  1.000580;0.888759;,
  0.989724;0.019750;,
  0.045168;0.051590;,
  0.054755;0.901711;,
  0.984672;0.892529;,
  0.975085;0.042409;,
  0.055721;0.030002;,
  0.052241;0.888243;,
  0.962130;0.893723;,
  0.966508;0.035069;,
  0.023289;0.036649;,
  0.022346;0.891515;,
  0.986427;0.892771;,
  0.988788;0.037067;,
  0.330291;0.717561;,
  0.394863;0.821769;,
  0.469885;0.682817;,
  0.392150;0.651992;,
  0.335904;0.485156;,
  0.166083;0.679654;,
  0.583737;0.748612;,
  0.752326;0.715264;,
  0.551382;0.658829;,
  0.311255;0.825557;,
  0.213935;0.677856;,
  0.108830;0.863341;,
  0.381900;0.287700;,
  0.371200;0.269300;,
  0.360900;0.295100;,
  0.385100;0.043800;,
  0.364300;0.052800;,
  0.389700;0.064600;,
  0.136800;0.286500;,
  0.155400;0.276000;,
  0.129500;0.265500;,
  0.138000;0.041700;,
  0.148700;0.060200;,
  0.159000;0.034500;,
  0.851378;0.483660;,
  0.071019;0.479520;,
  0.071778;0.552665;,
  0.853276;0.556460;,
  0.180976;0.883221;,
  0.830293;0.894044;,
  0.831826;0.817399;,
  0.180610;0.806918;,
  0.259745;0.882311;,
  0.907540;0.886031;,
  0.909117;0.820304;,
  0.260375;0.816273;,
  0.815457;0.793261;,
  -0.041458;0.782064;,
  -0.041273;0.843130;,
  0.810192;0.855209;,
  0.388000;0.269000;,
  0.364400;0.037100;,
  0.132300;0.060200;,
  0.155400;0.292400;,
  0.579878;0.070653;,
  0.576266;0.859052;,
  0.621098;0.860982;,
  0.624710;0.066406;,
  0.775587;0.882468;,
  0.784725;0.036783;,
  0.710692;0.034166;,
  0.704335;0.880301;,
  0.683346;0.097031;,
  0.684523;0.851823;,
  0.776206;0.851894;,
  0.779777;0.097143;,
  0.312276;0.042987;,
  0.320496;0.883934;,
  0.409311;0.883834;,
  0.403844;0.041207;;
 }
 MeshVertexColors {
  84;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;;
 }
}
