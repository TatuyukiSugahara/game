#pragma once
#include "..\pad\Pad.h"
#include "Frame\EffectManager.h"
#include "..\physics\Physics.h"

extern LPDIRECT3D9             g_pD3D;		
extern LPDIRECT3DDEVICE9       g_pd3dDevice;
extern CPad g_pad;			//�p�b�h�̃O���[�o��
extern EffectManager*			g_effectManager;
extern CPhysicsWorld			g_physicsWorld;