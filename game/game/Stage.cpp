#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable[] = {
#include "Collision_stage01.h"
};

SCollisionInfo collisionInfoTable2[] = {
#include "Collision_stage02.h"
};

SCollisionInfo collisionInfoTableBoss[] = {
#include "Collision_StageBos.h"
};

CStage* g_stage;

/*!-----------------------------------------------------------------------------
*@brief	ライトを更新。
-----------------------------------------------------------------------------*/
void CStage::UpdateLight()
{
	light.Update();
	lightback.Update();
}

void CStage::Init()
{
	//フィジックスワールド作成。
	g_physicsWorld = new CPhysicsWorld;
	//物理ワールド初期化
	g_physicsWorld->Init();		
	//NULLセット。
	memset(rigidBody, NULL, sizeof(rigidBody));
	memset(groundShape, NULL, sizeof(groundShape));
	//グローバルのステージに自分を設定。
	g_stage = this;
	//スプライト初期化
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
	}
	//ステージごとのコリジョン設定。
	//ステージごとに初期化
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		collisionTable = collisionInfoTable;
		arraySize = ARRAYSIZE(collisionInfoTable);
		//通常ステージ初期化
		StageInit();
		break;
	case CSceneManager::StageNumber::Stage2:
		collisionTable = collisionInfoTable2;
		arraySize = ARRAYSIZE(collisionInfoTable2);
		//通常ステージ初期化
		StageInit();
		break;
	case CSceneManager::StageNumber::StageBoss:
		collisionTable = collisionInfoTableBoss;
		arraySize = ARRAYSIZE(collisionInfoTableBoss);
		//ボスステージ初期化
		StageBossInit();
		break;
	}
}

void CStage::Update()
{
	//ステージごとに更新
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//通常ステージ更新
		StageUpdate();
		break;
	case CSceneManager::StageNumber::Stage2:
		//通常ステージ更新
		StageUpdate();
		break;
	case CSceneManager::StageNumber::StageBoss:
		//ボスステージ更新
		StageBossUpdate();
		break;
	}
}

void CStage::Render()
{
	//ステージごとに描画
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//通常ステージ描画
		StageRender();
		break;
	case CSceneManager::StageNumber::Stage2:
		//通常ステージ描画
		StageRender();
		break;
	case CSceneManager::StageNumber::StageBoss:
		//ボスステージ描画
		StageBossRender();
		break;
	}
}

void CStage::Release()
{
	//影リリース
	shadow.Release();
	//プレイヤーリリース
	player.Release();
}

void CStage::CreateCollision()
{
	if (arraySize >= MaxCollision)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionTable[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;
			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape[i], btVector3(0, 0, 0));
			rigidBody[i] = new btRigidBody(rbInfo);
		}
	}
}

void CStage::AddRigidBody()
{
	// ワールドに追加。
	if (!isAddCollision){
		isAddCollision = true;
		for (int i = 0; i < arraySize; i++)
		{
			g_physicsWorld->AddRigidBody(rigidBody[i]);
		}
	}
}

void CStage::BossMusic()
{
	//ボス戦の音楽を流す
	if (bossmusic == false)
	{
		//現在の音楽を止める
		soundsource.Stop();
		//ボス戦音楽を再生
		soundsource.InitStreaming("Asset/Sound/dotabatare-su.wav");
		soundsource.Play(true);
		bossmusic = true;
	}
}

void CStage::MusicStop()
{
	//だんだん音を下げる。
	soundsource.SetVolume(-0.005f);
}

//デバッグ用のステージ変更
void CStage::StageChange()
{
	//1を押すとステージ１へ
	if (GetAsyncKeyState('1'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage1);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
	//2を押すとステージ２へ
	else if (GetAsyncKeyState('2'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage2);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
	//3を押すとステージ３へ
	else if (GetAsyncKeyState('3'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::StageBoss);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
}

//通常ステージの初期化
void CStage::StageInit()
{
	//コリジョン作成
	CreateCollision();
	//リジッドボディ追加
	AddRigidBody();
	//ライトを初期化。
	light.Init();
	//カメラの初期化。
	camera.Init();
	skycamera.Init();
	//サウンド初期化
	soundsource.InitStreaming("Asset/Sound/CandyCrush.wav");
	soundsource.Play(true);
	//背景ライトを初期化
	lightback.Init();
	//ステージ背景初期化
	stageback.Init(g_pd3dDevice);
	//マップ初期化
	map.Init(g_pd3dDevice);
	//プレイヤー初期化
	player.Init(g_pd3dDevice);
	//モフルンエネミー初期化
	mohurun.Init();
	//nブロック初期化
	nblock.Init(g_pd3dDevice);
	//見えないブロック初期化
	//noblock.Init();
	//はてなボックス初期化
	//hanatebox.Init(g_pd3dDevice);
	//キノコ初期化
	//kinoko.Init(g_pd3dDevice);
	//土管初期化
	pipe.Init();
	//ゴール初期化
	goal.Init();
	//サボテン初期化
	//sabo.Init(g_pd3dDevice);
	//コインを初期化
	coin.Init();
	//ゴールフラグ初期化
	goalflag.Init();
	//鳥初期化
	bird.Init();
	//コインナンバー初期化
	coinNumber.Init();
	//コインスプライト初期化
	coinsprite.Init();
	//影初期化
	shadow.Create(512, 512);
	//太陽初期化
	sun.Init();
	//回転するギミック初期化
	//otationgimmick.Init();
	//亀初期化
	kame.Init();
}

//ボスステージ初期化
void CStage::StageBossInit()
{
	//コリジョン作成
	CreateCollision();
	//リジッドボディ追加
	AddRigidBody();
	//ライトを初期化。
	light.Init();
	//カメラの初期化。
	camera.Init();
	skycamera.Init();
	//サウンド初期化
	soundsource.InitStreaming("Asset/Sound/CandyCrush.wav");
	soundsource.Play(true);
	//背景ライトを初期化
	lightback.Init();
	//ステージ背景初期化
	stageback.Init(g_pd3dDevice);
	//マップ初期化
	map.Init(g_pd3dDevice);
	//プレイヤー初期化
	player.Init(g_pd3dDevice);
	//影初期化
	shadow.Create(512, 512);
	//太陽初期化
	sun.Init();
	//ボス音楽フラグ初期化。
	bossmusic = false;
	//ボス初期化
	boss.Init();
	//ボスライフ初期化
	bossLife.Init();
	//ボス名前初期化
	bossName.Init();
	//ボスカットイン初期化
	bossKatto.Init();
	//ボス撃破クリア初期化
	bossClear.Init();
}

//通常ステージ更新
void CStage::StageUpdate()
{
	//ライトの更新。
	UpdateLight();
	//ステージ背景更新
	stageback.Update();
	//マップ更新
	map.Update();
	//プレイヤーを更新。
	player.Update();
	//コイン更新
	coinNumber.Update();
	//コインスプライト更新
	coinsprite.Update();
	//影更新
	//ライトのポジションをプレイヤーの10m上に設定
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	//サウンドソース更新
	soundsource.Update();
	//太陽更新
	sun.Update();
	//モフルンエネミー更新
	mohurun.Update();
	//Nブロックを更新
	nblock.Update();
	//土管更新
	pipe.Update();
	//ゴール更新
	goal.Update();
	//サボテン更新
	//sabo.Update();
	//コイン更新
	coin.Update();
	//ゴールフラグ更新
	goalflag.Update();
	//鳥更新
	bird.Update();
	//回転するギミック更新
	//rotationgimmick.Update();
	//見えないブロック更新
	//noblock.Update();
	//はてなボックス更新
	//hanatebox.Update();
	//キノコ更新
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
	{
	kinoko.Update();
	}*/
	//亀更新
	kame.Update();
	//カメラの更新
	camera.Update();
	skycamera.Update();

#ifdef _DEBUG
	StageChange();
#endif
}

//ボスステージ更新
void CStage::StageBossUpdate()
{
	//ライトの更新。
	UpdateLight();
	//ステージ背景更新
	stageback.Update();
	//マップ更新
	map.Update();
	//プレイヤーを更新。
	player.Update();
	//コイン更新
	coinNumber.Update();
	//コインスプライト更新
	coinsprite.Update();
	//影更新
	//ライトのポジションをプレイヤーの10m上に設定
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	//サウンドソース更新
	soundsource.Update();
	//太陽更新
	sun.Update();
	//ボス更新
	boss.Update();
	//ボスライフ更新
	bossLife.Update();
	//ボス名前更新
	bossName.Update();
	//ボスカットイン更新
	bossKatto.Update();
	//ボスクリア更新
	bossClear.Update();
	//カメラの更新
	camera.Update();
	skycamera.Update();

#ifdef _DEBUG
	StageChange();
#endif
}

//通常ステージ描画
void  CStage::StageRender()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//影描画
	shadow.Render(camera.GetViewMatrix());
	//プレイヤー用の影描画
	shadow.RenderUnity(camera.GetViewMatrix());
	//レンダリングターゲットの切り替え。
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);		//現在のレンダリングターゲット
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);	//現在のデプスステンシルサーフェスをゲット。
	//メインレンダーターゲットに差し替える。
	g_pd3dDevice->SetRenderTarget(
		0,									//何番目のレンダリングターゲットを設定するかの引数。
		mainRenderTarget->GetRenderTarget()	//変更するレンダリングターゲット。
		);
	// デプスステンシルバッファも変更する。
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

	// レンダリングターゲットをクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//ステージ背景描画
	stageback.Render(
		skycamera.GetViewMatrix(),
		skycamera.GetProjectionMatrix()
		);
	//マップ描画
	map.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//プレイヤーを描画
	player.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false
		);
	//モフルンエネミー描画
	mohurun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//Nブロックを描画
	nblock.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//見えないブロック描画
	noblock.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//はてなボックス描画
	/*hanatebox.Render(
	g_pd3dDevice,
	camera.GetViewMatrix(),
	camera.GetProjectionMatrix(),
	light.GetLightDirection(),
	light.GetLightColor(),
	light.GetambientLight(),
	light.GetLightNum()
	);*/
	//キノコ
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
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
	}*/
	//土管描画
	pipe.Render(camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//ゴール描画
	goal.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
		);
	//サボテン描画
	/*sabo.Render(
	g_pd3dDevice,
	camera.GetViewMatrix(),
	camera.GetProjectionMatrix(),
	light.GetLightDirection(),
	light.GetLightColor(),
	light.GetambientLight(),
	light.GetLightNum()
	);*/
	//コイン描画
	coin.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//ゴール旗描画
	goalflag.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//鳥描画
	bird.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//回転するギミック描画
	/*rotationgimmick.Render(
	camera.GetViewMatrix(),
	camera.GetProjectionMatrix()
	);*/
	//太陽描画
	sun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//亀更新
	kame.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//コイン取得表示用(一番前に描画するためZバッファクリア)
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	coinsprite.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//ブルーム描画
	bloom->Render();
	//レンダリングターゲットを戻す。
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//参照カウンタが増えているので開放。
	frameBufferRT->Release();
	frameBufferDS->Release();

	//オフスクリーンレンダリングした絵をフレームバッファに貼り付ける。
	CopyMainRTToCurrentRT();

	//ブルーム完了後２D表示
	//コイン描画
	coinNumber.Render(sprite);

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

//ボスステージ描画
void CStage::StageBossRender()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//影描画
	shadow.Render(camera.GetViewMatrix());
	//プレイヤー用の影描画
	shadow.RenderUnity(camera.GetViewMatrix());

	//レンダリングターゲットの切り替え。
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);		//現在のレンダリングターゲット
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);	//現在のデプスステンシルサーフェスをゲット。
	//メインレンダーターゲットに差し替える。
	g_pd3dDevice->SetRenderTarget(
		0,									//何番目のレンダリングターゲットを設定するかの引数。
		mainRenderTarget->GetRenderTarget()	//変更するレンダリングターゲット。
		);
	// デプスステンシルバッファも変更する。
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

	// レンダリングターゲットをクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//ステージ背景描画
	stageback.Render(
		skycamera.GetViewMatrix(),
		skycamera.GetProjectionMatrix()
		);
	//マップ描画
	map.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//プレイヤーを描画
	player.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false
		);
	//太陽描画
	sun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//ボス描画
	boss.Render(camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//コイン取得表示用(一番前に描画するためZバッファクリア)
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//ブルーム描画
	bloom->Render();
	//レンダリングターゲットを戻す。
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//参照カウンタが増えているので開放。
	frameBufferRT->Release();
	frameBufferDS->Release();
	//オフスクリーンレンダリングした絵をフレームバッファに貼り付ける。
	CopyMainRTToCurrentRT();
	//ブルーム完了後２D表示
	//ボスライフ描画
	bossLife.Render(sprite);
	//ボスカットイン描画
	bossKatto.Render(sprite);
	//ボスクリア描画
	bossClear.Render(sprite);
	if (boss.Start() == true && boss.GetLife() > 0)
	{
		//ボス名前描画
		bossName.Render(sprite);
	}
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}