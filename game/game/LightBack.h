#pragma once

class CLightBack : public CLight
{
public:
	CLightBack();
	~CLightBack();
	void Init();
	void Update();
	void Draw();
	const D3DXVECTOR4* GetLightDirection() const
	{
		return m_diffuseLightDirection;
	}
	const D3DXVECTOR4* GetLightColor() const
	{
		return m_diffuseLightColor;
	}
	const D3DXVECTOR4& GetambientLight() const
	{
		return m_ambientLight;
	}
	const int& GetLightNum() const
	{
		return LIGHT_NUM;
	}
private:
	static const int		LIGHT_NUM = 5;
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				m_ambientLight;						//����
};

