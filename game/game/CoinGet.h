#pragma once 

class CCoinGet
{
public:
	CCoinGet();
	~CCoinGet();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//�|�W�V�����Z�b�g
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//��]�Z�b�g
	void SetRotFlag(const bool& flag)
	{
		rot = flag;
	}
private:
	SkinModel			skinModel;				//���f��
	SkinModelData		modelData;				//���f���f�[�^
	Animation			animation;				//�A�j���[�V����
	CLight				light;					//���C�g
	LPDIRECT3DTEXTURE9	normalMap = NULL;		//�m�[�}���}�b�v
	D3DXVECTOR3			position;				//���W
	D3DXVECTOR3			scale;					//�傫��
	D3DXQUATERNION		rotation;				//��]
	bool				rot = false;			//��]�t���O
	float				time = 0.0f;			//��]���鎞��
};