/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

//#include "LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4	g_worldMatrix;			//!<���[���h�s��B
float4x4 	g_viewMatrix;			//�r���[�s��B
float4x4 	g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4	g_rotationMatrix;		//!<��]�s��B
float4x4	g_viewMatrixRotInv;		//!<�J�����̉�]�s��̋t�s��B
float4x4 	g_mLVP;			//���C�g�r���[�v���W�F�N�V�����s��B //�����B
float3 		vEyePos;				//�J�����̈ʒu(��[���邴�Ђ傤)

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B
int g_ShadowReceiverFlag;							//�e���󂯂�t���O
int g_Ground;										//�n�ʂ��ǂ����̃t���O

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
texture g_shadowTexture;		//�V���h�[�e�N�X�`���B
texture g_shadowUnityTexture;	//���j�e�B�V���h�[�e�N�X�`��
texture g_normalTexture;		//�@���}�b�v�B
texture g_specularTexture;		//�X�y�L�����}�b�v�B

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
//���j�e�B�V���h�[�e�N�X�`��
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

//�@���}�b�v�B
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
int g_hasNormalMap;			//�@���}�b�v�����邩�t���O

//�X�y�L�����}�b�v
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
int g_isHasSpecularMap;		//�X�y�L�����}�b�v�ێ����Ă���H

/*!
 * @brief	���͒��_
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
    float3	Tangent			: TANGENT;		//�ڃx�N�g��
};

/*!
 * @brief	�o�͒��_�B
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
	float3	Tangent			: TEXCOORD5;		//�ڃx�N�g��
	float3	worldPos		: TEXCOORD6;
	
};
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
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
 *@brief	���[���h���W�ƃ��[���h�@�����v�Z�B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}

/*!
 *@brief	�X�y�L�������C�g���v�Z�B
 *@param[in]	worldPos		���[���h���W�n�ł̒��_���W�B
 *@param[in]	n				�@���B
 */
float3 CalcSpecular( float3 worldPos, float3 normal )
{
	float3 spec = 0.0f;
	
	float3 toEyeDir = normalize(vEyePos - worldPos);
	float3 R = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	for( int i = 0; i < DIFFUSE_LIGHT_NUM; i++ ){
		//�X�y�L�����������v�Z����B
		//���˃x�N�g�����v�Z�B
		float3 L = -g_diffuseLightDirection[i].xyz;
		spec += g_diffuseLightColor[i] * pow(max(0.0f, dot(L,R)), 5) * g_diffuseLightColor[i].w;	//�X�y�L�������x�B
	}
	return spec;
}

/*!
 *@brief	���_�V�F�[�_�[�B
 *@param[in]	In			���͒��_�B
 *@param[in]	hasSkin		�X�L������H
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent );
	}else{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent );
	}
  

	o.lightViewPos_1 = mul(float4(Pos,1.0f),g_mLVP );
	o.worldPos = Pos;
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
   
    //���ʔ��˗p�̃x�N�g��
    o.Eye = vEyePos - Pos.xyz;

    o.uv = In.uv;
    o.normal = normalize(Normal);
    o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;
	return o;
}
/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
float4 posInLVP = In.lightViewPos_1;
	posInLVP.xyz /= posInLVP.w;

	//uv���W�ɕϊ��B
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;
	
	float3 normal = In.normal;
	//�m�[�}���}�b�v
	if(g_hasNormalMap == true)
	{
		//�^���W�F���g�X�y�[�X�̖@�������[�h�B
		float3 localNormal = tex2D(g_normalMapSampler, In.Tex0);
		//���_�V�F�[�_�[����󂯎�����ڃx�N�g���𐳋K���B
		float3 tangent = normalize(In.Tangent);
		//���_�@���Ɛڃx�N�g�����g���ď]�@�������߂�B
		float3 biNormal = normalize( cross(tangent, normal) );
		
		//-1.0�`1.0�͈̔͂Ƀ}�b�s���O����B
		localNormal = (localNormal * 2.0f) - 1.0f;
		//�^���W�F���g�X�y�[�X���烏�[���h�X�y�[�X�ɕϊ�����B
		normal = tangent * localNormal.x
				+ biNormal * localNormal.y
				+ normal * localNormal.z;
		normal = normalize(normal);
	}
	//���C�g���v�Z�B
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
		//�X�y�L�����}�b�v������
		float3 spec = CalcSpecular(In.worldPos, normal);
		spec *= tex2D(g_specularMapSampler, In.Tex0).a;
		lig.xyz += spec;
		
	}
			
	
	
	color.xyz *= lig;
	return color;
}
/*!
*@brief	�e�p�s�N�Z���V�F�[�_�[�B
*/
float4 PSDrowToShadowMapMain(VS_OUTPUT In) : COLOR
{
	float z = In.lightViewPos_1.z / In.lightViewPos_1.w;
	return z;
}
/*!
 *@brief	�X�L�����胂�f���p�̃e�N�j�b�N�B
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
 *@brief	�X�L���Ȃ����f���p�̃e�N�j�b�N�B
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
*@brief		�X�L������e�p�̃e�N�j�b�N
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
*@brief	�X�L���Ȃ��e���f���p�̃e�N�j�b�N�B
*/
technique NoSkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}