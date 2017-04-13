#include "stdafx.h"
#include "System.h"
#include "..\BulletPhysics\BulletPhysics.h"

CPad					g_pad;					//�Q�[���p�b�h
LPDIRECT3D9             g_pD3D = NULL;		
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
EffectManager*			g_effectManager = NULL;
CPhysicsWorld*			g_physicsWorld = NULL;
CSceneManager*			g_scenemanager = NULL;
CSoundEngine*			g_soundengine = NULL;
CSkinModelDataManager*	g_skinmodeldataManager = NULL;
Bloom*					bloom = NULL;				//�u���[��


extern void Init();
extern void Render();
extern void Update();
extern void Terminate();
//-----------------------------------------------------------------------------
// DirectX���������B
//-----------------------------------------------------------------------------
void InitD3D(HWND hWnd)
{
	//D3D�I�u�W�F�N�g���쐬����B
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	// D3D�f�o�C�X���쐬���邽�߂̃p�����[�^��ݒ肷��B
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//D3D�f�o�C�X���쐬����B
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);
}
//-----------------------------------------------------------------------------
// ���b�Z�[�W�v���V�[�W���B
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (g_pd3dDevice != NULL)
			g_pd3dDevice->Release();

		if (g_pD3D != NULL)
			g_pD3D->Release();
		Terminate();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//-----------------------------------------------------------------------------
// �E�B�����C���B
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// �E�B���h�E�N���X��o�^�B
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Shader Tutorial", NULL
	};
	RegisterClassEx(&wc);

	// �E�B���h�E���쐬�B
	HWND hWnd = CreateWindow("Shader Tutorial", "Run Run Running",
		WS_OVERLAPPEDWINDOW, 100, 100, 960, 540,
		NULL, NULL, wc.hInstance, NULL);
	// Direct3D���������B
	InitD3D(hWnd);

	
	// Show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//��������Q�[���֌W�̏������B
	g_scenemanager = new CSceneManager;		//�V�[���}�l�[�W���[�쐬
	g_soundengine = new CSoundEngine;		//�T�E���h�G���W���쐬
	g_pad.Init(0);							//�p�b�h������
	g_bulletPhysics.InitPysics();			//����������
	g_effectManager = new EffectManager;				//�G�t�F�N�g�}�l�[�W���[�쐬
	g_skinmodeldataManager = new CSkinModelDataManager;//�X�L�����f�����[���}�l�[�W���[��������
	bloom = new Bloom;									//�u���[���쐬
	Init();
	
	// �Q�[�����[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			g_pad.Update();	//�p�b�h�A�b�v�f�[�g
			g_bulletPhysics.Update();		//�����G���W���X�V
			if (g_physicsWorld){
				g_physicsWorld->Update();		//�������[���h�X�V
			}
			Update();
			Render();
		}
	}
	UnregisterClass("Shader Tutorial", wc.hInstance);
	return 0;
}