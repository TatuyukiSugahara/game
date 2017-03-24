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
extern CPad g_pad;			//パッドのグローバル
extern EffectManager*			g_effectManager;
extern CPhysicsWorld*			g_physicsWorld;
extern CSceneManager*			g_scenemanager;
extern CSoundEngine*			g_soundengine;
extern CSkinModelDataManager*	g_skinmodeldataManager;
extern CRenderTarget*			mainRenderTarget;
extern Bloom*					bloom;				//ブルーム
extern void DrawQuadPrimitive();
extern void CopyMainRTToCurrentRT();

static const int FRAME_BUFFER_WITDH = 960;		//!<フレームバッファのサイズ。
static const int FRAME_BUFFER_HEIGHT = 540;		//!<フレームバッファのサイズ。