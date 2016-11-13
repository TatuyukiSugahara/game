#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>

#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "BulletPhysics\BulletPhysics.h"

#include "lib/System.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <list>

#include "Frame\SkinModel.h"
#include "Frame\SkinModelData.h"
#include "Frame\Animation.h"
#include "Light.h"

enum GameScene
{
	Title,		//タイトル画面
	Game,		//ゲーム画面
	Result,		//リザルト画面
};
extern GameScene scene;