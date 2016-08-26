/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Light.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "HatenaBox.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------
Camera camera;				//カメラ。
CLight light;				//ライト
CPlayer player;				//プレイヤー
CBlock block;				//ブロック
CStage stage;				//ステージ
CHatenaBox	hanatebox;		//はてなボックス

/*!-----------------------------------------------------------------------------
 *@brief	ライトを更新。
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	light.Update();
}
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//ライトを初期化。
	light.Init();
	//ステージ初期化
	stage.Initialize();
	//ブロック初期化
	block.Init(g_pd3dDevice);
	//はてなボックス初期化
	hanatebox.Init(g_pd3dDevice);
	//プレイヤー初期化
	player.Init(g_pd3dDevice);
	//カメラの初期化。
	camera.Init(&player);

}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	//ブロックを描画
	block.Render(
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
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	//ライトの更新。
	UpdateLight();
	//ステージ更新
	stage.Update();
	//ブロックを更新
	block.Update();
	//はてなボックス更新
	hanatebox.Update();
	//プレイヤーを更新。
	player.Update();
	//カメラの更新
	camera.Update();
	
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	//ブロックリリース
	block.Release();
	//はてなボックスリリース
	hanatebox.Release();
	//プレイヤーリリース
	player.Release();
}
