#pragma once


class CCoinChip
{
public:
	CCoinChip();
	~CCoinChip();
	//������
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//���W�Z�b�g
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//���_�Z�b�g
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	//�R�C���Q�b�g�������t���O�Q�b�g
	const bool& GetCoin() const
	{
		return coinGet;
	}
private:
	SkinModel						skinModel;		//���f��
	SkinModelData*					modelData;		//���f���f�[�^
	Animation						animation;		//�A�j���[�V����
	CLight							light;			//���C�g
	D3DXVECTOR3						position;		//���W
	D3DXVECTOR3						scale;			//�傫��
	D3DXVECTOR3						scaleShadow;	//�傫���e�p
	D3DXQUATERNION					rotation;		//��]
	bool							coinGet;		//�R�C�����Q�b�g�������t���O�B
	std::unique_ptr<CSoundSource>	soundSource;	//�R�C���Q�b�gSE
};

