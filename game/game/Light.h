#pragma once



class CLight
{
public:
	CLight();
	~CLight();
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
	/*!
	*@brief	平行光源の方向を設定。
	*@param[in]	lightNo		ライトの番号
	*@param[in]	dir			方向。
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	平行光源の色を設定。
	*@param[in]	lightNo		ライトの番号。
	*@param[in]	color		平行光源の色。
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	環境光を設定。
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		ambientLight = ambient;
	}
private:
	static const int		LIGHT_NUM = 4;
	D3DXVECTOR4 			diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				ambientLight;						//環境光
};

