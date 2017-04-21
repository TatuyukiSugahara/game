#pragma once
#include "..\pad\Pad.h"
#include "Frame\EffectManager.h"
#include "..\physics\Physics.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundEngine.h"
#include "../Sound/SoundSource.h"
#include "..\Frame\SkinModelDataManager.h"
#include "..\Frame\RenderTarget.h"
#include "../Frame/bloom.h"

extern LPDIRECT3D9             g_pD3D;		
extern LPDIRECT3DDEVICE9       g_pd3dDevice;
extern CPad g_pad;			//�p�b�h�̃O���[�o��
extern EffectManager*			g_effectManager;
extern CPhysicsWorld*			g_physicsWorld;
extern CSceneManager*			g_scenemanager;
extern CSoundEngine*			g_soundengine;
extern CSkinModelDataManager*	g_skinmodeldataManager;
extern CRenderTarget*			mainRenderTarget;
extern Bloom*					bloom;				//�u���[��
extern void DrawQuadPrimitive();
extern void CopyMainRTToCurrentRT();

static const int FRAME_BUFFER_WITDH = 960;		//!<�t���[���o�b�t�@�̃T�C�Y�B
static const int FRAME_BUFFER_HEIGHT = 540;		//!<�t���[���o�b�t�@�̃T�C�Y�B