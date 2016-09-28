#include "stdafx.h"
#include "Model.h"
#include "Stage.h"

LPDIRECT3DTEXTURE9 g_hoge = NULL;

//コンストラクタ
Model::Model()
{
	mesh = NULL;
	textures = NULL;
	numMaterial = 0;
	effect = NULL;
	ShadowReceiverFlag = false;
}
//デストラクタ
Model::~Model()
{
	Release();
}
//初期化。
void Model::Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName)
{
	Release();
	//Xファイルをロード。
	LPD3DXBUFFER pD3DXMtrlBuffer;
	//Xファイルのロード。
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	//法線が存在するか調べる。
	if ((mesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		//法線がないので作成する。
		ID3DXMesh* pTempMesh = NULL;

		mesh->CloneMeshFVF(mesh->GetOptions(),
			mesh->GetFVF() | D3DFVF_NORMAL, g_pd3dDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		mesh->Release();
		mesh = pTempMesh;

	}

	// マテリアルバッファを取得。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//テクスチャをロード。
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		char* baseDir = "Asset/model/";
		char filePath[64];
		strcpy(filePath, baseDir);
		strcat(filePath, d3dxMaterials[i].pTextureFilename);
		textures[i] = NULL;
		//テクスチャを作成する。
		D3DXCreateTextureFromFileA(pd3dDevice,
			filePath,
			&textures[i]);
	}
	// マテリアルバッファを解放。
	pD3DXMtrlBuffer->Release();

	//シェーダーをコンパイル。
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//シェーダーをコンパイル。
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,
		"basic.fx",
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&effect,
		&compileErrorBuffer
		);
	if (hr != S_OK) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}
//描画。
void Model::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX worldMatrix,
	D3DXMATRIX rotationMatrix,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isDrawToShadowMap
	)
{
	if (isDrawToShadowMap == true)
	{
		effect->SetTechnique("RenderShadowMap");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		
		D3DXMATRIX mWVP;
		mWVP = worldMatrix * g_stage.GetShadow()->Getlvpmatrix();
		//視点設定
		effect->SetMatrix("g_mWVP", &mWVP);

		

		for (DWORD i = 0; i < numMaterial; i++)
		{
			effect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
			// Draw the mesh subset
			mesh->DrawSubset(i);
		}

		effect->EndPass();
		effect->End();
	}
	else
	{
		effect->SetTechnique("SkinModel");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		//定数レジスタに設定するカラー。
		D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
		//ワールド行列の転送。
		effect->SetMatrix("g_worldMatrix", &worldMatrix);
		//ビュー行列の転送。
		effect->SetMatrix("g_viewMatrix", &viewMatrix);			//ビュー行列を転送。

		effect->SetMatrix("g_projectionMatrix", &projMatrix);	//プロジェクション行列の転送。

		effect->SetMatrix("g_rotationMatrix", &rotationMatrix);		//回転行列を転送。
		//ライトの向きを転送。
		effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
		//ライトのカラーを転送。
		effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
		//環境光を設定。
		effect->SetVector("g_ambientLight", &ambientLight);
		//視点設定
		effect->SetVector("vEyePos", &(D3DXVECTOR4)g_stage.GetCamera()->GetEyePt());

		effect->SetInt("g_ShadowReceiverFlag", ShadowReceiverFlag);//影フラグ
		//if (ShadowReceiverFlag == true)
		{
			effect->SetTexture("g_shadowTexture", g_hoge);//影
			effect->SetMatrix("g_lightVPMatrix", &g_stage.GetShadow()->Getlvpmatrix());
		}
		for (DWORD i = 0; i < numMaterial; i++)
		{

			effect->SetTexture("g_diffuseTexture", textures[i]);
			effect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
			// Draw the mesh subset
			mesh->DrawSubset(i);
		}
		
		effect->EndPass();
		effect->End();
	}
	
}
//開放。
void Model::Release()
{
	//メッシュを開放。
	if (mesh != NULL) {
		mesh->Release();
		mesh = NULL;
	}
	//テクスチャを開放。
	if (textures != NULL) {
		for (unsigned int i = 0; i < numMaterial; i++) {
			if (textures[i] != NULL) {
				textures[i]->Release();
				textures[i] = NULL;
			}
		}
		delete[] textures;
		textures = NULL;
	}
	//エフェクトを開放。
	if (effect != NULL) {
		effect->Release();
		effect = NULL;
	}
}