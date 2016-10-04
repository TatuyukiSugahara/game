/*!
 *@brief	�ȒP�ȃf�B�t���[�Y���C�e�B���O�̃V�F�[�_�[�B
 */


float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix;			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4 g_rotationMatrix;		//��]�s��B�@������]�����邽�߂ɕK�v�ɂȂ�B���C�e�B���O����Ȃ�K�{�B
float4x4 g_lightVPMatrix;		//���C�g�r���[�v���W�F�N�V�����}�g���N�X
float3 vEyePos;				//�J�����̈ʒu(��[���邴�Ђ傤)

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B

int g_ShadowReceiverFlag;

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
texture g_shadowTexture;		//�V���h�[�e�N�X�`���B

sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
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

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3	normal	: NORMAL0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: TEXCOORD1;
	float3  Eye	: TEXCOORD2;
	float4  lightViewPos : TEXCOORD3;
};

/*!
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	//���W�ϊ�
	float4 pos; 
	pos = mul( In.pos, g_worldMatrix );		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	float4 worldPos = pos;
	pos = mul( pos, g_viewMatrix );			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul( pos, g_projectionMatrix );	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	//����+�g�U��
	float amb = -g_diffuseLightDirection[0].w;
	float3 L = -g_diffuseLightDirection[0].xyz; //���[�J���̃��C�g���W
	Out.color = In.color * max(amb,dot(In.normal,-g_diffuseLightDirection[0].xyz));
	//���ʔ��˗p�̃x�N�g��
	Out.Eye = vEyePos - pos.xyz;
	
	if(g_ShadowReceiverFlag == true)
	{
		Out.lightViewPos = mul(float4(worldPos.xyz, 1.0f), g_lightVPMatrix);
	}
	
	Out.uv = In.uv;
	Out.normal = mul(In.normal, g_worldMatrix);	//�@�����񂷁B
	return Out;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	//���C�g���v�Z�B
	float4 lig = 0.0f;
	{
		for( int i = 0; i < DIFFUSE_LIGHT_NUM; i++ ){
			lig.xyz += max( 0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz) ) 
					* g_diffuseLightColor[i].xyz;
			//�X�y�L�������v�Z�B
			float3 L = -g_diffuseLightDirection[i].xyz;
			float3 H = normalize(L + normalize(In.Eye));//�n�[�t�x�N�g��
			float3 N = normalize(In.normal);
			lig.xyz += pow(max(0.0f, dot(N, H)), 10.0f);
		}
		lig += g_ambientLight;
	}
	float4 color = tex2D(g_diffuseTextureSampler, In.uv);
	if (g_ShadowReceiverFlag == 1)
	{
		float4 posInLVP = In.lightViewPos;
		posInLVP.xyz /= posInLVP.w;
		//uv���W�ɕϊ��B
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
		if((shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f) && (shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f))
		{
			color *= tex2D(g_shadowTextureSampler, shadowMapUV);
		}
	}
	color.xyz *= lig.xyz;
	return color;
}

technique SkinModel
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMain();
		PixelShader 	= compile ps_3_0 PSMain();
	}
}