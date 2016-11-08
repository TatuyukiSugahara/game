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
	*@brief	���s�����̕�����ݒ�B
	*@param[in]	lightNo		���C�g�̔ԍ�
	*@param[in]	dir			�����B
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	���s�����̐F��ݒ�B
	*@param[in]	lightNo		���C�g�̔ԍ��B
	*@param[in]	color		���s�����̐F�B
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	������ݒ�B
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}
private:
	static const int		LIGHT_NUM = 4;
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				m_ambientLight;						//����
};

