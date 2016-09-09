#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable2D[] = {
#include "Collision2D_stage01.h"
};

CStage g_stage;

/*!-----------------------------------------------------------------------------
*@brief	ライトを更新。
-----------------------------------------------------------------------------*/
void CStage::UpdateLight()
{
	light.Update();
}

void CStage::Initialize()
{
	CreateCollision2D();
	Add2DRigidBody(ARRAYSIZE(collisionInfoTable2D));
	//ライトを初期化。
	light.Init();
	//ステージ背景初期化
	stageback.Init(g_pd3dDevice);
	//マップ初期化
	map.Init(g_pd3dDevice);
	//プレイヤー初期化
	player.Init(g_pd3dDevice);
	//ブロック初期化
	block.Init(g_pd3dDevice);
	//nブロック初期化
	nblock.Init(g_pd3dDevice);
	//はてなボックス初期化
	hanatebox.Init(g_pd3dDevice);
	//キノコ初期化
	kinoko.Init(g_pd3dDevice);
	//土管初期化
	pipe.Init(g_pd3dDevice);
	//カメラの初期化。
	camera.Init(&player);
	
}

void CStage::Update()
{
	//ライトの更新。
	UpdateLight();
	//ステージ背景更新
	stageback.Update();
	//マップ更新
	map.Update();
	//プレイヤーを更新。
	player.Update();
	//ブロックを更新
	block.Update();
	//Nブロックを更新
	nblock.Update();
	//はてなボックス更新
	hanatebox.Update();
	//キノコ更新
	if (hanatebox.GetItem() == true && kinoko.GetKinoko() == false)
	{
		kinoko.Update();
	}
	//土管更新
	pipe.Update();
	//カメラの更新
	camera.Update();
}

void CStage::Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	//ステージ背景描画
	stageback.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//マップ描画
	map.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//プレイヤーを描画
	player.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//ブロックを描画
	/*block.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);*/
	//Nブロックを描画
	nblock.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//はてなボックス描画
	hanatebox.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//キノコ
	if (hanatebox.GetItem() == true && kinoko.GetKinoko() == false)
	{
		kinoko.Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			light.GetLightDirection(),
			light.GetLightColor(),
			light.GetambientLight(),
			light.GetLightNum()
			);
	}
	//土管描画
	pipe.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
	);
		
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CStage::Release()
{
	//ステージ背景リリース
	stageback.Release();
	//ブロックリリース
	block.Release();
	//はてなボックスリリース
	hanatebox.Release();
	//キノコリリース
	kinoko.Release();
	//プレイヤーリリース
	player.Release();
	//土管リリース
	pipe.Release();
}

void CStage::CreateCollision2D()
{
	int arraySize = ARRAYSIZE(collisionInfoTable2D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable2D[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody2D[i] = new btRigidBody(rbInfo);

			//ワールドに追加。
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);

		}
	}
}

void CStage::Add2DRigidBody(int arraySize)//ワールドに追加。
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
		}
	}
}
