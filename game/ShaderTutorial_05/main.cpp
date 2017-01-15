/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "stage.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Scene\SceneManager.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//scene = GameScene::Title;
	////タイトルシーン初期化
	//g_titlescene.Init();
	////ステージ初期化
	//g_stage->Init();
	////リザルト画面
	//g_resultscene.Init();
	//サウンドエンジン
	g_soundengine->Init();
	g_scenemanager->InitializeScene();
	
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	//switch (scene)
	//{
	//case Title:
	//	//タイトルシーン描画
	//	g_titlescene.Render();
	//	break;
	//case Game:
	//	//ステージ描画
	//	g_stage->Render();
	//	break;
	//case Result:
	//	//リザルト画面
	//	g_resultscene.Render();
	//	break;
	//}
	g_scenemanager->RenderScene();
	
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	//switch (scene)
	//{
	//case Title:
	//	//タイトルシーン更新
	//	g_titlescene.Update();
	//	break;
	//case Game:
	//	//ステージ更新
	//	g_stage->Update();
	//	break;
	//case Result:
	//	//リザルト画面
	//	g_resultscene.Update();
	//	break;
	//}
	//サウンドエンジン
	g_soundengine->Update();
	g_soundsource->Update();
	g_scenemanager->UpdateScene();
	
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	//ステージリリース
	if (g_stage){
		g_stage->Release();
		delete g_stage;
	}
	if (g_effectManager){
		delete g_effectManager;
	}
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
