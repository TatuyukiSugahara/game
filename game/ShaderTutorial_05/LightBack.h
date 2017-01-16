#pragma once

class CLightBack : public CLight
{
public:
	CLightBack();
	~CLightBack();
	void Init();
	void Update();
	void Draw();
	D3DXVECTOR4* GetLightDirection()
	{
		return m_diffuseLightDirection;
	}
	D3DXVECTOR4* GetLightColor()
	{
		return m_diffuseLightColor;
	}
	D3DXVECTOR4 GetambientLight()
	{
		return m_ambientLight;
	}
	int GetLightNum()
	{
		return LIGHT_NUM;
	}
private:
	static const int		LIGHT_NUM = 5;
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				m_ambientLight;						//環境光
};

