/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "stage.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Scene\SceneManager.h"
#include "Particle\Primitive.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------
CRenderTarget* mainRenderTarget;	//!<18-2 ���C�������_�����O�^�[�Q�b�g�B
CPrimitive*	quadPrimitive;			//!<18-3 �l�p�`�̔|���v���~�e�B�u�B
LPD3DXEFFECT copyEffect;			//!<18-3 �R�s�[���s���V�F�[�_�[�B
LPD3DXEFFECT monochromeEffect;		//!<18-4 ���m�N���t�B���^�[��������V�F�[�_�[�B

//-----------------------------------------------------------------------------
// �|����`��B
//-----------------------------------------------------------------------------
void DrawQuadPrimitive()
{
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
		//����͐擪����ǂݍ��ނ̂�0�ł����B
		quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
		);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
		);
}
//-----------------------------------------------------------------------------
// Name: 18-2 ���C�������_�����O�^�[�Q�b�g���������B
//-----------------------------------------------------------------------------
void InitMainRenderTarget()
{
	mainRenderTarget = new CRenderTarget;
	mainRenderTarget->Create(
		FRAME_BUFFER_WITDH,			//�����_�����O�^�[�Q�b�g�̕��ƍ����̓t���[���o�b�t�@�Ɠ����ɂ��Ă����B(�K�����������ł���K�v�͂Ȃ��I�I�I)
		FRAME_BUFFER_HEIGHT,
		1,							//�~�b�v�}�b�v���x���B�����1�ł����B�~�b�v�}�b�v�o���Ă܂����H
		D3DFMT_A16B16G16R16F,		//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g�B16bit�̕��������_�o�b�t�@���w�肷��B
		D3DFMT_D24S8,				//�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B��ʓI��16bit��24bit�t�H�[�}�b�g���g���邱�Ƃ������B�����24bit�t�H�[�}�b�g���g���B
		D3DMULTISAMPLE_NONE,		//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0							//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
		);
}
//-----------------------------------------------------------------------------
// Name: 18-3 �|���̏������B
//-----------------------------------------------------------------------------
void InitQuadPrimitive()
{
	// �n���Y�I�� 2
	quadPrimitive = new CPrimitive;
	//���_�̍\���́B
	struct SVertex {
		float pos[4];	//���_���W�B
		float uv[2];		//UV���W�B
	};
	//���_�o�b�t�@�B
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//���_���C�A�E�g�B���_�o�b�t�@�̍\�����ǂ̂悤�ɂȂ��Ă��邩��GPU�ɋ����邽�߂̂��́B
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//���_�X�g���[����0�Ԗڂ�0�o�C�g�ڂ���float�^��4���̃f�[�^�͍��W(D3DDECLUSAGE_POSITION)�ł��邱�Ƃ������Ă���B
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		//���_�X�g���[����0�Ԗڂ�16�o�C�g�ڂ���float�^��2���̃f�[�^��UV���W(D3DDECLUSAGE_TEXCOORD)�ł��邱�Ƃ������Ă���B
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	//�C���f�b�N�X�o�b�t�@�B
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//����̓v���~�e�B�u�̎�ނ̓g���C�A���O���X�g���b�v�B
		4,							//���_�̐��B�l�p�`�̔|���Ńg���C�A���O���X�g���b�v�Ȃ̂łS�B
		sizeof(SVertex),			//���_�X�g���C�h�B��̒��_�̑傫���B�P�ʂ̓o�C�g�B
		scShapeVertex_PT_Element,	//���_���C�A�E�g�B
		vertexBuffer,				//���_�o�b�t�@�B
		4,							//�C���f�b�N�X�̐��B
		D3DFMT_INDEX16,				//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B�����16bit�t�H�[�}�b�g���w�肷��B
		//�C���f�b�N�X�̐���65536�ȉ��̏ꍇ��16bit�ł������A����𒴂���ꍇ��D3DFMT_INDEX32���w�肷��B
		indexBuffer					//�C���f�b�N�X�o�b�t�@�B
		);
}
//-----------------------------------------------------------------------------
// Name: 18-3 ���C�������_�����O�^�[�Q�b�g�̓��e�����݂̃����_�����O�^�[�Q�b�g�ɃR�s�[�B
//-----------------------------------------------------------------------------
void CopyMainRTToCurrentRT()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ���u�����h������Ȃ��B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	LPD3DXEFFECT shader = copyEffect;			//18-3 �R�s�[���s���V�F�[�_�[���g���ꍇ�͂�����B
	//LPD3DXEFFECT shader = monochromeEffect;		//18-4 ���m�N���t�B���^�[��������ꍇ�͂�������g�p����B
	//�V�F�[�_�[��ݒ�B
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//�V�[���e�N�X�`����ݒ肷��
	float size[2] = {
		0.5f / (float)(mainRenderTarget->GetWidth()),
		0.5f / (float)(mainRenderTarget->GetHeight())
	};
	shader->SetValue("size", size, sizeof(size));
	shader->SetTexture("g_tex", mainRenderTarget->GetTexture());
	//�萔���W�X�^�ւ̕ύX���R�~�b�g����B
	shader->CommitChanges();
	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
//-----------------------------------------------------------------------------
// Name: �V�F�[�_�[�����[�h�B
//-----------------------------------------------------------------------------
void LoadShaders()
{
	// �n���Y�I�� 4
	// �R�s�[���s���V�F�[�_�[�����[�h�B
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Asset/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&copyEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
	// ���m�N���t�B���^�[���s���V�F�[�_�[�����[�h�B
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Asset/Shader/MonochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&monochromeEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 ���C�������_�����O�^�[�Q�b�g���쐬����B
	InitMainRenderTarget();
	//18-3 �l�p�`�̔|���v���~�e�B�u���쐬�B
	InitQuadPrimitive();
	//18-3�A18-4 �V�F�[�_�[�����[�h�B
	LoadShaders();
	//�T�E���h�G���W��
	g_soundengine->Init();
	g_scenemanager->InitializeScene();
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	//�V�[���̕`��J�n�B
	//g_pd3dDevice->BeginScene();

	


	// �V�[���������_�����O�B
	g_scenemanager->RenderScene();

	
	
	// �V�[���̕`��I���B
	//g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	//g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	//�T�E���h�G���W��
	g_soundengine->Update();
	g_scenemanager->UpdateScene();
	
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	//�X�e�[�W�����[�X
	if (g_stage){
		g_stage->Release();
		//delete g_stage;
	}
	if (g_effectManager){
		delete g_effectManager;
	}
	if (g_skinmodeldataManager)
	{
		delete g_skinmodeldataManager;
	}
	delete mainRenderTarget;	//18-2
	delete quadPrimitive;		//18-3
	copyEffect->Release();		//18-3
	/*g_pd3dDevice->Release();
	g_pD3D->Release();*/
}
