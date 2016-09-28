#pragma once
#include "Texture.h"

class Model {
public:
	//コンストラクタ
	Model();
	//デストラクタ
	~Model();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName);

	//描画。
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX worldMatrix,
		D3DXMATRIX rotationMatrix,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isDrawToShadowMap
		);
	//開放。
	void Release();
	LPD3DXMESH GetMesh()
	{
		return mesh;
	}
	ID3DXEffect* GetEffect()
	{
		return effect;
	}
	void SetEffect(ID3DXEffect*	effect)
	{
		this->effect = effect;
	}
	void SetShadowReceiverFlag(bool flag)
	{
		ShadowReceiverFlag = flag;
	}
private:
	LPD3DXMESH				mesh;			//メッシュ。
	LPDIRECT3DTEXTURE9*		textures;		//テクスチャ。
	DWORD					numMaterial;	//マテリアルの数。
	ID3DXEffect*			effect;			//エフェクト。	
	CTexture				tex;			//テクスチャロード
	bool					ShadowReceiverFlag;
};