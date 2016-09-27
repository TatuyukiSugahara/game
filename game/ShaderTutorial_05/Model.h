#pragma once
#include "Texture.h"

class Model {
public:
	//�R���X�g���N�^
	Model();
	//�f�X�g���N�^
	~Model();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName);

	//�`��B
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX worldMatrix,
		D3DXMATRIX rotationMatrix,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//�J���B
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
private:
	LPD3DXMESH				mesh;			//���b�V���B
	LPDIRECT3DTEXTURE9*		textures;		//�e�N�X�`���B
	DWORD					numMaterial;	//�}�e���A���̐��B
	ID3DXEffect*			effect;			//�G�t�F�N�g�B	
	CTexture				tex;			//�e�N�X�`�����[�h
};