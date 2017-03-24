#pragma once

class CMapChip
{
public:
	CMapChip();
	~CMapChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//���W���Z�b�g
	void SetPos(const D3DXVECTOR3& pos)
	{
		position=pos;
	}
	//��]���Z�b�g
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
private:
	SkinModel			skinModel;	//���f��
	SkinModelData*		modelData;	//���f���f�[�^
	Animation			animation;	//�A�j���[�V����
	CLight				light;		//���C�g
	D3DXVECTOR3			position;	//���W
	D3DXQUATERNION		rotation;	//��]
};

