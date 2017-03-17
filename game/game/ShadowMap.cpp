#include "stdafx.h"
#include"ShadowMap.h"
#include "Stage.h"


void CShadowMap::Create(int w, int h)
{
	RenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	RenderTargetUnity.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	this->h = h;
	this->w = w;


	Near = 0.1f;
	Far = 30.0f;
}


void CShadowMap::Render(D3DXMATRIX viewMatrix)
{
	g_pd3dDevice->GetViewport(&viewport);
	//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂����߃o�b�N�A�b�v���s��
	g_pd3dDevice->GetRenderTarget(0, &Backbuffer);
	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂�����
	g_pd3dDevice->GetDepthStencilSurface(&BackZ);
	//�����_�����O�^�[�Q�b�g��ύX����
	g_pd3dDevice->SetRenderTarget(0, RenderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTarget.GetDepthStencilBuffer());
	//�������ݐ��ύX�����̂ŃN���A
	g_pd3dDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//�ˉe�s����쐬
	D3DXMatrixOrthoLH(&projMatrix, 20.0f, 20.0f, Near, Far);
	//���C�g�쐬�X�V
	CreateLight(projMatrix);

	//�m�[�}���u���b�N�̉e��`��
	g_stage->GetNBlock()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//�G���ӂ��̉e��`��
	g_stage->GetMohu()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//�G���̉e��`��
	g_stage->GetBird()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//�R�C���̉e��`��
	g_stage->GetCoin()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//�{�X�̉e��`��
	g_stage->GetBoss()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//�T�̉e��`��
	g_stage->GetKame()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//���̃����_�[�^�[�Q�b�g�ɖ߂�
	g_pd3dDevice->SetRenderTarget(0, Backbuffer);
	g_pd3dDevice->SetDepthStencilSurface(BackZ);
	g_pd3dDevice->SetViewport(&viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�e�N�X�`���Z�b�g
	g_shadow = RenderTarget.GetTexture();
}

void CShadowMap::RenderUnity(D3DXMATRIX viewMatrix)
{
	g_pd3dDevice->GetViewport(&viewport);
	//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂����߃o�b�N�A�b�v���s��
	g_pd3dDevice->GetRenderTarget(0, &Backbuffer);
	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂�����
	g_pd3dDevice->GetDepthStencilSurface(&BackZ);
	//�����_�����O�^�[�Q�b�g��ύX����
	g_pd3dDevice->SetRenderTarget(0, RenderTargetUnity.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTargetUnity.GetDepthStencilBuffer());
	//�������ݐ��ύX�����̂ŃN���A
	g_pd3dDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//�ˉe�s����쐬
	D3DXMatrixOrthoLH(&projMatrix, 20.0f, 20.0f, Near, Far);
	//���C�g���쐬�X�V
	CreateLight(projMatrix);
	//�v���C���[�̉e��`��
	g_stage->GetPlayer()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//���̃����_�[�^�[�Q�b�g�ɖ߂�
	g_pd3dDevice->SetRenderTarget(0, Backbuffer);
	g_pd3dDevice->SetDepthStencilSurface(BackZ);
	g_pd3dDevice->SetViewport(&viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�v���C���[�̉e�e�N�X�`���Z�b�g
	g_Unity = RenderTargetUnity.GetTexture();
}

void CShadowMap::CreateLight(D3DXMATRIX proj)
{
	//���C�g�r���[�v���W�F�N�V�����s����X�V
	D3DXVECTOR3 lightUp;
	//�����������
	float t = fabsf(D3DXVec3Dot(&lightDirection, &CConst::Vec3Up));
	if (fabsf((t - 1.0f)) < 0.00001f)
	{
		//�قڐ^�ォ�^��
		lightUp = CConst::Vec3Right;
	}
	else
	{
		lightUp = CConst::Vec3Up;
	}
	D3DXVECTOR3 target;
	D3DXVec3Add(&target, &lightPosition, &lightDirection);
	D3DXMatrixLookAtLH(&lvMatrix, &lightPosition, &target, &lightUp);
	D3DXMatrixMultiply(&LVPMatrix, &lvMatrix, &projMatrix);
}

void CShadowMap::Release()
{
	if (pEffect != nullptr) {
		pEffect = nullptr;
	}
}
