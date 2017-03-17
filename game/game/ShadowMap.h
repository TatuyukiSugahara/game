#pragma once

#include"RenderTarget.h"
#include "Frame\SkinModel.h"

extern LPDIRECT3DTEXTURE9 g_shadow;
extern LPDIRECT3DTEXTURE9 g_Unity;

class CShadowMap
{
public:
	//�R���X�g���N�^
	CShadowMap(){
		pEffect = NULL;
	}
	//�f�X�g���N�^
	~CShadowMap(){
		Release();
	}
	//RenderTarget�쐬
	void Create(int w, int h);
	//���C�g�쐬
	void CreateLight(D3DXMATRIX);
	//�e�`��
	void Render(D3DXMATRIX viewMatrix);
	//�v���C���[�p�e�`��B
	void RenderUnity(D3DXMATRIX viewMatrix);
	//�����[�X
	void Release();
	//���C�g�r���[�v���W�F�Q�b�g
	const D3DXMATRIX& Getlvpmatrix() const
	{
		return lVPMatrix;
	}
	//���C�g�̍��W�Q�b�g
	void SetLightPosition(const D3DXVECTOR3& pos)
	{
		lightPosition = pos;
	}
	//���C�g�̕����Z�b�g
	void SetLightDirection(const D3DXVECTOR3& Dir)
	{
		lightDirection = Dir;
	}
	//�G�t�F�N�g�Z�b�g
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	//�G�t�F�N�g�Q�b�g
	const ID3DXEffect* GetEffect() const 
	{
		return pEffect;
	}
	/*!
	* @brief	�ߕ��ʁB
	*/
	const float& GetNear() const
	{
		return Near;
	}
	/*!
	* @brief	������
	*/
	const float& GetFar() const
	{
		return Far;
	}
private:
	D3DVIEWPORT9		viewport;				//�e�N�X�`���̃r���[�|�[�g
	LPDIRECT3DSURFACE9	backBuffer;				//�����_�[�^�[�Q�b�g�o�b�N�A�b�v
	LPDIRECT3DSURFACE9	backZ;					//�f�v�X�o�b�t�@�o�b�N�A�b�v
	CRenderTarget		renderTarget;			//�V���h�[�}�b�v���������ރ����_�[�^�[�Q�b�g
	CRenderTarget		renderTargetUnity;		//�V���h�[�}�b�v���������ރv���C���[�p�����_�[�^�[�Q�b�g
	D3DXVECTOR3			lightPosition;			//���C�g�̍��W
	D3DXVECTOR3			lightDirection;			//���C�g�̕���
	D3DXMATRIX			lvMatrix;				//���C�g�r���[�}�g���N�X
	D3DXMATRIX			lVPMatrix;				//���C�g�r���[�v���W�F�}�g���N�X
	D3DXMATRIX			projMatrix;				//�v���W�F
	D3DXMATRIX			worldMatrix;			//���[���h
	ID3DXEffect*		pEffect;				//�G�t�F�N�g
	float				Near;					//�ߕ��ʁB
	float				Far;					//�����ʁB
	int					width;					//��
	int					height;					//�c
};