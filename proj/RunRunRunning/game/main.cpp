/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "Map\stage.h"
#include "Title/TitleScene.h"
#include "Result/ResultScene.h"
#include "Scene\SceneManager.h"
#include "Particle\Primitive.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------
CRenderTarget* mainRenderTarget;	//!< メインレンダリングターゲット。
CPrimitive*	quadPrimitive;			//!< 四角形の板ポリプリミティブ。
LPD3DXEFFECT copyEffect;			//!< コピーを行うシェーダー。
LPD3DXEFFECT monochromeEffect;		//!< モノクロフィルターをかけるシェーダー。

//-----------------------------------------------------------------------------
// 板ポリを描画。
//-----------------------------------------------------------------------------
void DrawQuadPrimitive()
{
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
		//今回は先頭から読み込むので0でいい。
		quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
		);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		quadPrimitive->GetNumPolygon()			//プリミティブの数。
		);
}
//-----------------------------------------------------------------------------
// メインレンダリングターゲットを初期化。
//-----------------------------------------------------------------------------
void InitMainRenderTarget()
{
	mainRenderTarget = new CRenderTarget;
	mainRenderTarget->Create(
		FRAME_BUFFER_WITDH,			//レンダリングターゲットの幅と高さはフレームバッファと同じにしておく。(必ずしも同じである必要はない！！！)
		FRAME_BUFFER_HEIGHT,
		1,							//ミップマップレベル。これは1でいい。ミップマップ覚えてますか？
		D3DFMT_A16B16G16R16F,		//レンダリングターゲットのフォーマット。16bitの浮動小数点バッファを指定する。
		D3DFMT_D24S8,				//デプスステンシルバッファのフォーマット。一般的に16bitと24bitフォーマットが使われることが多い。今回は24bitフォーマットを使う。
		D3DMULTISAMPLE_NONE,		//マルチサンプリングの種類。今回はマルチサンプリングは行わないのでD3DMULTISAMPLE_NONEでいい。
		0							//マルチサンプリングの品質レベル。今回はマルチサンプリングは行わないので0でいい。
		);
}
//-----------------------------------------------------------------------------
// 板ポリの初期化。
//-----------------------------------------------------------------------------
void InitQuadPrimitive()
{
	quadPrimitive = new CPrimitive;
	//頂点の構造体。
	struct SVertex {
		float pos[4];	//頂点座標。
		float uv[2];		//UV座標。
	};
	//頂点バッファ。
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの。
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
		//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
		);
}
//-----------------------------------------------------------------------------
// メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー。
//-----------------------------------------------------------------------------
void CopyMainRTToCurrentRT()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	LPD3DXEFFECT shader = copyEffect;			// コピーを行うシェーダーを使う場合はこちら。
	//LPD3DXEFFECT shader = monochromeEffect;		// モノクロフィルターをかける場合はこちらを使用する。
	//シェーダーを設定。
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	float size[2] = {
		0.5f / (float)(mainRenderTarget->GetWidth()),
		0.5f / (float)(mainRenderTarget->GetHeight())
	};
	shader->SetValue("size", size, sizeof(size));
	shader->SetTexture("g_tex", mainRenderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();
	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
//-----------------------------------------------------------------------------
// Name: シェーダーをロード。
//-----------------------------------------------------------------------------
void LoadShaders()
{
	// コピーを行うシェーダーをロード。
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Asset/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&copyEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
	// モノクロフィルターを行うシェーダーをロード。
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Asset/Shader/MonochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&monochromeEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

//-----------------------------------------------------------------------------
// ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	// メインレンダリングターゲットを作成する。
	InitMainRenderTarget();
	// 四角形の板ポリプリミティブを作成。
	InitQuadPrimitive();
	// シェーダーをロード。
	LoadShaders();
	//サウンドエンジン
	g_soundengine->Init();
	g_scenemanager->InitializeScene();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// シーンをレンダリング。
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
	//サウンドエンジン
	g_soundengine->Update();
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
		//delete g_stage;
	}
	if (g_effectManager){
		delete g_effectManager;
	}
	if (g_skinmodeldataManager)
	{
		delete g_skinmodeldataManager;
	}
	delete mainRenderTarget;	
	delete quadPrimitive;		
	copyEffect->Release();		
	/*g_pd3dDevice->Release();
	g_pD3D->Release();*/
}
