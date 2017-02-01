/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

//#include "LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4 	g_viewMatrix;			//ビュー行列。
float4x4 	g_projectionMatrix;	//プロジェクション行列。
float4x4	g_rotationMatrix;		//!<回転行列。
float4x4	g_viewMatrixRotInv;		//!<カメラの回転行列の逆行列。
float4x4 	g_mLVP;			//ライトビュープロジェクション行列。 //環境光。
float3 		vEyePos;				//カメラの位置(ろーかるざひょう)

#define DIFFUSE_LIGHT_NUM	4		//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;								//環境光。
int g_ShadowReceiverFlag;							//影を受けるフラグ
int g_Ground;										//地面かどうかのフラグ

texture g_diffuseTexture;		//ディフューズテクスチャ。
texture g_shadowTexture;		//シャドーテクスチャ。
texture g_shadowUnityTexture;	//ユニティシャドーテクスチャ
texture g_normalTexture;		//法線マップ。
texture g_specularTexture;		//スペキュラマップ。

sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

sampler g_shadowTextureSampler =
sampler_state
{
	Texture = <g_shadowTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
//ユニティシャドーテクスチャ
sampler g_shadowUnityTextureSampler =
sampler_state
{
	Texture = <g_shadowUnityTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//法線マップ。
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};
int g_hasNormalMap;			//法線マップがあるかフラグ

//スペキュラマップ
sampler g_specularMapSampler = 
sampler_state
{
	Texture = <g_specularTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};
int g_isHasSpecularMap;		//スペキュラマップ保持している？

/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
     float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float4  color		: COLOR0;
	float3  normal		: NORMAL0;
	float2	uv		: TEXCOORD1;
    float3  Tex0            : TEXCOORD0;
    float3	Tangent			: TANGENT;		//接ベクトル
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
	float4	color	: COLOR0;
	float2	uv	: TEXCOORD1;
	float3	normal	: TEXCOORD2;
	float3  Eye	: TEXCOORD3;
    float2  Tex0   			: TEXCOORD0;
	float4  lightViewPos_1	: TEXCOORD4;
	float3	Tangent			: TEXCOORD5;		//接ベクトル
	float3	worldPos		: TEXCOORD6;
	
};
/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}

/*!
 *@brief	スペキュラライトを計算。
 *@param[in]	worldPos		ワールド座標系での頂点座標。
 *@param[in]	n				法線。
 */
float3 CalcSpecular( float3 worldPos, float3 normal )
{
	float3 spec = 0.0f;
	
	float3 toEyeDir = normalize(vEyePos - worldPos);
	float3 R = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	for( int i = 0; i < DIFFUSE_LIGHT_NUM; i++ ){
		//スペキュラ成分を計算する。
		//反射ベクトルを計算。
		float3 L = -g_diffuseLightDirection[i].xyz;
		spec += g_diffuseLightColor[i] * pow(max(0.0f, dot(L,R)), 5) * g_diffuseLightColor[i].w;	//スペキュラ強度。
	}
	return spec;
}

/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent );
	}
  

	o.lightViewPos_1 = mul(float4(Pos,1.0f),g_mLVP );
	o.worldPos = Pos;
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);	//ビュー空間から射影空間に変換。
   
    //鏡面反射用のベクトル
    o.Eye = vEyePos - Pos.xyz;

    o.uv = In.uv;
    o.normal = normalize(Normal);
    o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;
	return o;
}
/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
float4 posInLVP = In.lightViewPos_1;
	posInLVP.xyz /= posInLVP.w;

	//uv座標に変換。
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;
	
	float3 normal = In.normal;
	//ノーマルマップ
	if(g_hasNormalMap == true)
	{
		//タンジェントスペースの法線をロード。
		float3 localNormal = tex2D(g_normalMapSampler, In.Tex0);
		//頂点シェーダーから受け取った接ベクトルを正規化。
		float3 tangent = normalize(In.Tangent);
		//頂点法線と接ベクトルを使って従法線を求める。
		float3 biNormal = normalize( cross(tangent, normal) );
		
		//-1.0～1.0の範囲にマッピングする。
		localNormal = (localNormal * 2.0f) - 1.0f;
		//タンジェントスペースからワールドスペースに変換する。
		normal = tangent * localNormal.x
				+ biNormal * localNormal.y
				+ normal * localNormal.z;
		normal = normalize(normal);
	}
	//ライトを計算。
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			lig.xyz += max(0.0f, dot(normal.xyz, -g_diffuseLightDirection[i].xyz))
				* g_diffuseLightColor[i].xyz;
			float3 spec = lig.xyz;
		}
		lig += g_ambientLight;
	}
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	
	if(g_ShadowReceiverFlag == true)
	{
		if ((shadowMapUV.x > 0.0f && shadowMapUV.x <1.0f) && (shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f))
		{
			float z = tex2D(g_shadowUnityTextureSampler, shadowMapUV).x;
			if(g_Ground == true)
			{
				z = min(z, tex2D(g_shadowTextureSampler, shadowMapUV).x);
			}
			if(z < posInLVP.z - 0.0006f)
			{
				color *= 0.5f;
			}
		}
	}
	
	if (g_isHasSpecularMap){
		//スペキュラマップがある
		float3 spec = CalcSpecular(In.worldPos, normal);
		spec *= tex2D(g_specularMapSampler, In.Tex0).a;
		lig.xyz += spec;
		
	}
			
	
	
	color.xyz *= lig;
	return color;
}
/*!
*@brief	影用ピクセルシェーダー。
*/
float4 PSDrowToShadowMapMain(VS_OUTPUT In) : COLOR
{
	float z = In.lightViewPos_1.z / In.lightViewPos_1.w;
	return z;
}
/*!
 *@brief	スキンありモデル用のテクニック。
 */
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	スキンなしモデル用のテクニック。
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}
/*
*@brief		スキンあり影用のテクニック
*/
technique SkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}

/*!
*@brief	スキンなし影モデル用のテクニック。
*/
technique NoSkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}