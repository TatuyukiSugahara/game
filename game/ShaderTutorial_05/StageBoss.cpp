//#pragma once
//#include "stdafx.h"
//#include "StageBoss.h"
//
//SCollisionInfo collisionInfoTableBoss[] = {
//#include "CollisionStageBos.h"
//};
//
//CStageBoss* g_stageBoss;
//
///*!-----------------------------------------------------------------------------
//*@brief	ライトを更新。
//-----------------------------------------------------------------------------*/
//void CStageBoss::UpdateLight()
//{
//	light.Update();
//}
//
//void CStageBoss::Init()
//{
//	g_physicsWorld = new CPhysicsWorld;
//	g_physicsWorld->Init();			//物理ワールド初期化
//	memset(m_rigidBody, NULL, sizeof(m_rigidBody));
//	memset(m_groundShape, NULL, sizeof(m_groundShape));
//	g_stageBoss = this;
//
//	collisionTable = collisionInfoTableBoss;
//	arraySize = ARRAYSIZE(collisionInfoTableBoss);
//
//	CreateCollision();
//	Add2DRigidBody();
//	//ライトを初期化。
//	light.Init();
//	//カメラの初期化。
//	camera.Init();
//
//	//サウンドソースを初期化。
//	soundsource.InitStreaming("Asset/Sound/mario.wav");
//	soundsource.Play(true);
//	soundsource.SetVolume(0.5f);
//
//	//スプライト初期化
//	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
//	{
//		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
//	}
//
//	//ステージ背景初期化
//	stageback.Init(g_pd3dDevice);
//	//マップ初期化
//	map.Init(g_pd3dDevice);
//	//プレイヤー初期化
//	player.Init(g_pd3dDevice);
//	//影初期化
//	shadow.Create(512, 512);
//	//太陽初期化
//	sun.Init();
//	//ボス初期化
//	boss.Init();
//	//ボスライフ初期化
//	bossLife.Init();
//}
//
//void CStageBoss::Update()
//{
//	//ライトの更新。
//	UpdateLight();
//	//ステージ背景更新
//	stageback.Update();
//	//マップ更新
//	map.Update();
//	//プレイヤーを更新。
//	player.Update();
//	//影更新
//	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
//	shadow.SetLightPosition(lightPos);
//	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
//	D3DXVec3Normalize(&lightDir, &lightDir);
//	shadow.SetLightDirection(lightDir);
//	//サウンドソース更新
//	soundsource.Update();
//	//太陽更新
//	sun.Update();
//	//ボス更新
//	boss.Update();
//	//ボスライフ更新
//	bossLife.Update();
//	//カメラの更新
//	camera.Update();
//}
//
//void CStageBoss::Render()
//{
//	// 画面をクリア。
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
//	//シーンの描画開始。
//	g_pd3dDevice->BeginScene();
//
//	//影描画
//	shadow.Draw(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//	shadow.RenderUnity(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//
//	//ハンズオン 1-1 レンダリングターゲットの切り替え。
//	LPDIRECT3DSURFACE9 frameBufferRT;
//	LPDIRECT3DSURFACE9 frameBufferDS;
//	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);		//現在のレンダリングターゲット
//	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);	//現在のデプスステンシルサーフェスをゲット。
//	//メインレンダーターゲットに差し替える。
//	g_pd3dDevice->SetRenderTarget(
//		0,									//何番目のレンダリングターゲットを設定するかの引数。
//		mainRenderTarget->GetRenderTarget()	//変更するレンダリングターゲット。
//		);
//	// デプスステンシルバッファも変更する。
//	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
//
//	// レンダリングターゲットをクリア。
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
//
//	//ステージ背景描画
//	stageback.Render(
//		g_pd3dDevice,
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//	//マップ描画
//	map.Render(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix());
//	//プレイヤーを描画
//	player.Render(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix(),
//		false
//		);
//	//太陽描画
//	sun.Render();
//	if (g_scenemanager->GetNomber() == StageBoss)
//	{
//		//ボス描画
//		boss.Render();
//	}
//
//	//コイン取得表示用(一番前に描画するためZバッファクリア)
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
//		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
//	bloom->Render();									//ブルームレンダー
//	//// ハンズオン 1-2 レンダリングターゲットを戻す。
//	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
//	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
//	//参照カウンタが増えているので開放。
//	frameBufferRT->Release();
//	frameBufferDS->Release();
//
//	//// 18-3 オフスクリーンレンダリングした絵をフレームバッファに貼り付ける。
//	CopyMainRTToCurrentRT();
//
//	//ブルーム完了後２D表示
//	//ボスライフ描画
//	bossLife.Render(m_pSprite);
//	// シーンの描画終了。
//	g_pd3dDevice->EndScene();
//	// バックバッファとフロントバッファを入れ替える。
//	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
//}
//
//void CStageBoss::Release()
//{
//	//影リリース
//	shadow.Release();
//	//プレイヤーリリース
//	player.Release();
//}
//
//void CStageBoss::CreateCollision()
//{
//	if (arraySize >= MAX_COLLISION)
//	{
//		std::abort();
//	}
//	for (int i = 0; i < arraySize; i++) {
//		SCollisionInfo& collision = collisionTable[i];
//		//ここで剛体とかを登録する。
//		//剛体を初期化。
//		{
//			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
//			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
//			btTransform groundTransform;
//			groundTransform.setIdentity();
//			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
//			float mass = 0.0f;
//
//			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//			m_myMotionState = new btDefaultMotionState(groundTransform);
//			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
//			m_rigidBody[i] = new btRigidBody(rbInfo);
//
//			//ワールドに追加。
//			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
//
//		}
//	}
//}
//
//void CStageBoss::Add2DRigidBody(/*int arraySize*/)//ワールドに追加。
//{
//	if (!m_isAdd2DCollision){
//		m_isAdd2DCollision = true;
//		for (int i = 0; i < arraySize; i++)
//		{
//			g_physicsWorld->AddRigidBody(m_rigidBody[i]);
//		}
//	}
//}
