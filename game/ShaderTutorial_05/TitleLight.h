#pragma once

class CTitleLight
{
public:
	CTitleLight();
	~CTitleLight();
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
	/*!
	*@brief	平行光源の方向を設定。
	*@param[in]	lightNo		ライトの番号
	*@param[in]	dir			方向。
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	平行光源の色を設定。
	*@param[in]	lightNo		ライトの番号。
	*@param[in]	color		平行光源の色。
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	環境光を設定。
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}
private:
	static const int		LIGHT_NUM = 4;
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				m_ambientLight;						//環境光
};

