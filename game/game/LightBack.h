#pragma once

class CLightBack : public CLight
{
public:
	CLightBack();
	~CLightBack();
	void Init();
	void Update();
	void Draw();
	//ライトの方向ゲット
	const D3DXVECTOR4* GetLightDirection() const
	{
		return diffuseLightDirection;
	}
	//ライトのカラーゲット
	const D3DXVECTOR4* GetLightColor() const
	{
		return diffuseLightColor;
	}
	//環境光ゲット
	const D3DXVECTOR4& GetambientLight() const
	{
		return ambientLight;
	}
	//ライトの数ゲット
	const int& GetLightNum() const
	{
		return LIGHT_NUM;
	}
private:
	static const int		LIGHT_NUM = 5;						//ライトの数
	D3DXVECTOR4 			diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				ambientLight;						//環境光
};

