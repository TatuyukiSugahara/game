#pragma once 

class CCoinSprite
{
public:
	CCoinSprite();
	~CCoinSprite();
	void Init();
	void Update();
	void Render();
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRotFlag(bool flag)
	{
		rot = flag;
	}
private:
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	LPDIRECT3DTEXTURE9 normalMap = NULL;					//ノーマルマップ
	D3DXMATRIX							mRot;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;

	bool								rot = false;
	float								time = 0.0f;
};