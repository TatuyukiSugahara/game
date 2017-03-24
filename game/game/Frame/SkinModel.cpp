#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelData.h"
#include "..\Light\Light.h"
#include "..\Map\Stage.h"


extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;

LPDIRECT3DTEXTURE9 g_shadow = NULL;
LPDIRECT3DTEXTURE9 g_Unity = NULL;

void SkinModel::DrawMeshContainer(
	IDirect3DDevice9* pd3dDevice,
	LPD3DXMESHCONTAINER pMeshContainerBase,
	LPD3DXFRAME pFrameBase,
	ID3DXEffect* pEffect,
	D3DXMATRIX* worldMatrix,
	D3DXMATRIX* rotationMatrix,
	D3DXMATRIX* viewMatrix,
	D3DXMATRIX* projMatrix,
	CLight* light,
	LPDIRECT3DTEXTURE9 normal,
	LPDIRECT3DTEXTURE9 specularMap,
	bool isDrawToShadowMap
	)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iAttrib;
	LPD3DXBONECOMBINATION pBoneComb;

	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);
	D3DXMATRIX viewProj;
	D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
	if (pMeshContainer->pSkinInfo != NULL) {
		//顔以外のモデルの描画
		if (isDrawToShadowMap == TRUE)
		{
			//影用のテクニックを設定
			pEffect->SetTechnique("SkinModelDrowToShadowMap");
		}
		else
		{
			pEffect->SetTechnique("SkinModel");
		}
	}
	else {
		//顔のモデルの描画
		if (isDrawToShadowMap == TRUE)
		{
			//影用のテクニックを設定
			pEffect->SetTechnique("NoSkinModelDrowToShadowMap");
		}
		else
		{
			if (!SkyCube)
			{
				pEffect->SetTechnique("NoSkinModel");
			}
			else
			{
				//空描画用テクニック。
				pEffect->SetTechnique("Sky");
			}
			
		}
	}
	

	//ライトビュープロジェクション行列の計算。
	D3DXMATRIX LVP;
	if (g_stage)
	{
		LVP = g_stage->GetShadow()->Getlvpmatrix();
	}
	/*if (g_stageBoss)
	{
		LVP = g_stageBoss->GetShadow()->Getlvpmatrix();
	}
	*/
	//定数レジスタに設定するカラー。
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//ワールド行列の転送。
	pEffect->SetMatrix("g_worldMatrix", worldMatrix);
	//ビュー行列の転送。
	pEffect->SetMatrix("g_viewMatrix", viewMatrix);
	//プロジェクション行列の転送。
	pEffect->SetMatrix("g_projectionMatrix", projMatrix);
	//回転行列を転送。
	pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
	//ライトの向きを転送。
	pEffect->SetVectorArray("g_diffuseLightDirection", light->GetLightDirection(), light->GetLightNum());
	////ライトのカラーを転送。
	pEffect->SetVectorArray("g_diffuseLightColor", light->GetLightColor(), light->GetLightNum());
	////環境光を設定。
	pEffect->SetVector("g_ambientLight", &light->GetambientLight());
	//影のフラグを転送。
	//StageでフラグをTRUEにしている
	pEffect->SetInt("g_ShadowReceiverFlag", ShadowReceiverFlag);
	//ライトビュープロジェクション行列の転送。
	pEffect->SetMatrix("g_mLVP", &LVP);
	//ビュープロジェクション。
	pEffect->SetMatrix("g_mViewProj", &viewProj);
	//視点。
	pEffect->SetVector("vEyePos", &(D3DXVECTOR4)g_stage->GetCamera()->GetEyePt());

	//フレネルセットフラグ。
	pEffect->SetInt("hureneruflg", hureneruflg);

	//影を描画しているレンダーターゲットのテクスチャを取得。
	if (ShadowReceiverFlag == TRUE)
	{
		pEffect->SetBool("g_Ground", Ground);
		pEffect->SetTexture("g_shadowTexture", g_shadow);
		pEffect->SetTexture("g_shadowUnityTexture", g_Unity);
	}
	//共通の定数レジスタを設定
	{
		//ライト
		pEffect->SetValue(
			"g_light",
			light,
			sizeof(CLight)
			);
		if (isNormalMap == true)
		{
			if (normal != NULL)
			{
				//法線マップがある場合
				pEffect->SetTexture("g_normalTexture", normal);
				pEffect->SetInt("g_hasNormalMap", isNormalMap);
			}
		}
		else
		{
			//法線マップがない場合
			pEffect->SetTexture("g_normalTexture", NULL);
			pEffect->SetInt("g_hasNormalMap", isNormalMap);
		}
		if (isSpecularMap == true)
		{
			if (specularMap != NULL) {
				//スペキュラマップがあるので、シェーダーに転送する。
				pEffect->SetTexture("g_specularTexture", specularMap);
				//スペキュラマップのあり、なしのフラグをtrueにする。
				pEffect->SetInt("g_isHasSpecularMap", isSpecularMap);
			}
		}
		else 
		{
			//スペキュラマップのあり、なしのフラグをfalseにする。
			pEffect->SetTexture("g_specularTexture", NULL);
			pEffect->SetInt("g_isHasSpecularMap", isSpecularMap);
		}

		if (pMeshContainer->pSkinInfo != NULL)
		{
			//スキン情報有り。
			pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				// first calculate all the world matrices
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(
							&g_pBoneMatrices[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
							);
						//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
					}
				}

				pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
				pEffect->SetInt("g_numBone", pMeshContainer->NumInfl);
				// ディフューズテクスチャ。
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				// ボーン数。
				pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
				D3DXMATRIX viewRotInv;
				D3DXMatrixInverse(&viewRotInv, NULL, viewMatrix);
				viewRotInv.m[3][0] = 0.0f;
				viewRotInv.m[3][1] = 0.0f;
				viewRotInv.m[3][2] = 0.0f;
				viewRotInv.m[3][3] = 1.0f;
				D3DXMatrixTranspose(&viewRotInv, &viewRotInv);
				pEffect->SetMatrix("g_viewMatrixRotInv", &viewRotInv);
				pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
				pEffect->BeginPass(0);
				pEffect->CommitChanges();
				// draw the subset with the current world matrix palette and material state
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);

				pEffect->EndPass();
				pEffect->End();
			}
		}
		else 
		{
			D3DXMATRIX mWorld;
			if (pFrame != NULL) {
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else {
				mWorld = *worldMatrix;
			}
			//pEffect->SetTexture("g_normalTexture", NULL);
			pEffect->SetMatrix("g_worldMatrix", &mWorld);
			pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
			pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
			pEffect->BeginPass(0);
			if (!SkyCube)
			{
				for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {

					pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
					pEffect->CommitChanges();
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
			else
			{
				for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {

					pEffect->SetTexture("g_skyCubeMap", texture.GetCubeMapDX());
					pEffect->CommitChanges();
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
			pEffect->EndPass();
			pEffect->End();
		}
	}
	//mesh = pMeshContainer->MeshData.pMesh;
}
void SkinModel::DrawFrame(
	IDirect3DDevice9* pd3dDevice,
	LPD3DXFRAME pFrame,
	ID3DXEffect* pEffect,
	D3DXMATRIX* worldMatrix,
	D3DXMATRIX* rotationMatrix,
	D3DXMATRIX* viewMatrix,
	D3DXMATRIX* projMatrix,
	CLight* light,
	LPDIRECT3DTEXTURE9 normal,
	LPDIRECT3DTEXTURE9 specularMap,
	bool isDrawToShadowMap
	)
{
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(
			pd3dDevice,
			pMeshContainer,
			pFrame,
			pEffect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normal,
			specularMap,
			isDrawToShadowMap
			);

		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(
			pd3dDevice,
			pFrame->pFrameSibling,
			pEffect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normal,
			specularMap,
			isDrawToShadowMap
			);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(
			pd3dDevice,
			pFrame->pFrameFirstChild,
			pEffect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normal,
			specularMap,
			isDrawToShadowMap
			);
	}
}
SkinModel::SkinModel() :
	skinModelData(nullptr),
	light(nullptr),
	pEffect(nullptr)
{
}
SkinModel::~SkinModel()
{
}

void SkinModel::Init(SkinModelData* modelData)
{
	ShadowReceiverFlag = false;
	isDrawToShadowMap = false;
	isNormalMap = false;
	isSpecularMap = false;
	Ground = false;
	pEffect = g_effectManager->LoadEffect("Asset/Shader/Model.fx");
	skinModelData = modelData;
	CreateMeshList(skinModelData->GetFrameRoot());
}
void SkinModel::UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	D3DXMATRIX mTrans, mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

	worldMatrix = mScale * rotationMatrix * mTrans;

	if (skinModelData) {
		skinModelData->UpdateBoneMatrix(worldMatrix);	//ボーン行列を更新。
	}
}

void SkinModel::Render(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix,bool isDrawToShadowMap)
{
	if (skinModelData) {
		DrawFrame(
			g_pd3dDevice, 
			skinModelData->GetFrameRoot(), 
			pEffect,
			&worldMatrix,
			&rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normalMap,
			specularMap,
			isDrawToShadowMap
		);
	}
}

/*!
* @brief	先頭のメッシュを取得。
*/
LPD3DXMESH SkinModel::GetOrgMeshFirst() const
{
	return skinModelData->GetOrgMeshFirst();
}

/*!
* @brief	オリジナルメッシュを取得。
*/
LPD3DXMESH SkinModel::GetOrgMesh(LPD3DXFRAME frame) const
{
	return skinModelData->GetOrgMesh(frame);
}

//メッシュをツリー構造で調べて作成する
void SkinModel::CreateMeshList(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	//メッシュがある
	while (pMeshContainer != NULL)
	{
		//顔？
		if (strcmp(pFrame->Name, "_face") == 0)
		{
			meshList.push_back(GetMesh(pMeshContainer));
		}
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	//兄弟がいる?
	if (pFrame->pFrameSibling != NULL)
	{
		CreateMeshList(pFrame->pFrameSibling);
	}
	//子供がいる？
	if (pFrame->pFrameFirstChild != NULL)
	{
		CreateMeshList(pFrame->pFrameFirstChild);
	}
}

//メッシュをゲット
const LPD3DXMESH& SkinModel::GetMesh(const LPD3DXMESHCONTAINER& pMeshContainerBase) const
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

	return pMeshContainer->MeshData.pMesh;
}


//モーフィング処理の実行。
//morphTargetA	モーフターゲット笑顔
//morphTargetB　もーふターゲット真顔
//rate モーフィングレート。
void SkinModel::Morphing(SkinModel* morphTargetA, SkinModel* morphTargetB, float rate)
{
	//メッシュのサイズ分回す
	for (unsigned int i = 0; i < meshList.size(); i++)
	{
		LPD3DXMESH targetMesh_A = morphTargetA->GetMeshList()[i];
		//モーフターゲットAの頂点バッファを取得する。
		LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_A;
		targetMesh_A->GetVertexBuffer(&targetVertexBuffer_A);
		//頂点バッファの定義を取得する。
		D3DVERTEXBUFFER_DESC desc;
		targetVertexBuffer_A->GetDesc(&desc);
	
		//頂点ストライドを計算する。
		int stride = desc.Size / targetMesh_A->GetNumVertices();

		//モーフターゲットBのメッシュを取得する。
		LPD3DXMESH targetMesh_B = morphTargetB->GetMeshList()[i];
		//モーフターゲットBの頂点バッファを取得する。
		LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_B;
		targetMesh_B->GetVertexBuffer(&targetVertexBuffer_B);
		targetVertexBuffer_B->GetDesc(&desc);
		//自分の頂点バッファを取得する。
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		GetMeshList()[i]->GetVertexBuffer(&vertexBuffer);
		vertexBuffer->GetDesc(&desc);
		D3DXVECTOR3* vertexPos;
		D3DXVECTOR3* targetVertexPos_A;
		D3DXVECTOR3* targetVertexPos_B;
		//頂点バッファをロック。
		vertexBuffer->Lock(0, desc.Size, (void**)&vertexPos, D3DLOCK_DISCARD);
		targetVertexBuffer_A->Lock(0, desc.Size, (void**)&targetVertexPos_A, D3DLOCK_DISCARD);
		targetVertexBuffer_B->Lock(0, desc.Size, (void**)&targetVertexPos_B, D3DLOCK_DISCARD);
		for (unsigned int vertNo = 0; vertNo < targetMesh_A->GetNumVertices(); vertNo++) {
			///////////////////////////////////////////////////////////////////
			//ここに頂点モーフの処理を記述する。
			///////////////////////////////////////////////////////////////////
			*vertexPos = *targetVertexPos_A * (1.0f - rate) + *targetVertexPos_B * rate;

			//次の頂点へ。
			char* p = (char*)vertexPos;

			p += stride;
			vertexPos = (D3DXVECTOR3*)p;
			p = (char*)targetVertexPos_A;
			p += stride;
			targetVertexPos_A = (D3DXVECTOR3*)p;
			p = (char*)targetVertexPos_B;
			p += stride;
			targetVertexPos_B = (D3DXVECTOR3*)p;
		}
		//頂点バッファをアンロック。
		vertexBuffer->Unlock();
		targetVertexBuffer_A->Unlock();
		targetVertexBuffer_B->Unlock();
		vertexBuffer->Release();
		targetVertexBuffer_A->Release();
		targetVertexBuffer_B->Release();
	}
	
}