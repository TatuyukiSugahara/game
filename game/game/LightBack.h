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
		return diffuseLightDirection;
	}
	const D3DXVECTOR4* GetLightColor() const
	{
		return diffuseLightColor;
	}
	const D3DXVECTOR4& GetambientLight() const
	{
		return ambientLight;
	}
	const int& GetLightNum() const
	{
		return LIGHT_NUM;
	}
private:
	static const int		LIGHT_NUM = 5;
	D3DXVECTOR4 			diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				ambientLight;						//����
};

