#pragma once


class CCoinChip
{
public:
	CCoinChip();
	~CCoinChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRot(D3DXQUATERNION rot)
	{
		rotation = rot;
	}
	bool GetCoin()
	{
		return coinget;
	}
private:
	SkinModel skinmodel;
	SkinModelData* modelData;
	Animation animation;
	CLight	light;
	D3DXMATRIX							mRot;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	D3DXMATRIX							mWorld;			//���[���h�s��B
	int									size;
	bool								coinget;		//�R�C�����Q�b�g�������t���O�B

	CSoundSource* soundSource;
};

