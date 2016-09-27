/*!
 * @brief	�V���h�E�}�b�v�B
 */
struct VS_INPUT
{
	float4	Position	: POSITION;
};
struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float4 depth	: TEXCOORD;
};

float4x4	g_mWVP;		//���[���h�r���[�v���W�F�N�V�����s��B
float2		g_farNear;	//�����ʂƋߕ��ʁBx�ɉ����ʁAy�ɋߕ��ʁB
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	Out.Position = mul(In.Position, g_mWVP);
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	//�[�x���������ށB
	return float4(0.5f,0.5f,0.5f,1.0f);
}

technique RenderShadowMap
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}
