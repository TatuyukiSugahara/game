#pragma once



class CLight
{
public:
	CLight();
	~CLight();
	void Init();
	void Update();
	void Draw();
	//���C�g�̕����Q�b�g
	const D3DXVECTOR4* GetLightDirection() const
	{
		return diffuseLightDirection;
	}
	//���C�g�̃J���[�Q�b�g
	const D3DXVECTOR4* GetLightColor() const
	{
		return diffuseLightColor;
	}
	//�����Q�b�g
	const D3DXVECTOR4& GetambientLight() const
	{
		return ambientLight;
	}
	//���C�g�̐��Q�b�g
	const int& GetLightNum() const
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
		diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	���s�����̐F��ݒ�B
	*@param[in]	lightNo		���C�g�̔ԍ��B
	*@param[in]	color		���s�����̐F�B
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	������ݒ�B
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		ambientLight = ambient;
	}
private:
	static const int		LIGHT_NUM = 4;						//���C�g�̐�
	D3DXVECTOR4 			diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				ambientLight;						//����
};

