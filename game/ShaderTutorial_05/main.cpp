/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "stage.h"
#include "TitleScene.h"
#include "ResultScene.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	scene = GameScene::Title;
	//タイトルシーン初期化
	g_titlescene.Init();
	//ステージ初期化
	g_stage = new CStage;
	g_stage->Initialize();
	//リザルト画面
	g_resultscene.Init();

	
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	switch (scene)
	{
	case Title:
		//タイトルシーン描画
		g_titlescene.Render();
		break;
	case Game:
		//ステージ描画
		g_stage->Render();
		break;
	case Result:
		//リザルト画面
		g_resultscene.Render();
		break;
	}
	
	
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
	switch (scene)
	{
	case Title:
		//タイトルシーン更新
		g_titlescene.Update();
		break;
	case Game:
		//ステージ更新
		g_stage->Update();
		break;
	case Result:
		//リザルト画面
		g_resultscene.Update();
		break;
	}
	
	
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	//ステージリリース
	g_stage->Release();
	delete g_stage;
	delete g_effectManager;
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
