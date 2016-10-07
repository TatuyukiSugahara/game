#pragma once
#include "..\pad\Pad.h"
#include "Frame\EffectManager.h"


extern LPDIRECT3D9             g_pD3D;		
extern LPDIRECT3DDEVICE9       g_pd3dDevice;
extern CPad g_pad;			//パッドのグローバル
extern EffectManager*			g_effectManager;