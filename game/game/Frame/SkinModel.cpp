#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelData.h"
#include "..\Light.h"
#include "..\Stage.h"


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
		//��ȊO�̃��f���̕`��
		if (isDrawToShadowMap == TRUE)
		{
			//�e�p�̃e�N�j�b�N��ݒ�
			pEffect->SetTechnique("SkinModelDrowToShadowMap");
		}
		else
		{
			pEffect->SetTechnique("SkinModel");
		}
	}
	else {
		//��̃��f���̕`��
		if (isDrawToShadowMap == TRUE)
		{
			//�e�p�̃e�N�j�b�N��ݒ�
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
				//��`��p�e�N�j�b�N�B
				pEffect->SetTechnique("Sky");
			}
			
		}
	}
	

	//���C�g�r���[�v���W�F�N�V�����s��̌v�Z�B
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
	//�萔���W�X�^�ɐݒ肷��J���[�B
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//���[���h�s��̓]���B
	pEffect->SetMatrix("g_worldMatrix", worldMatrix);
	//�r���[�s��̓]���B
	pEffect->SetMatrix("g_viewMatrix", viewMatrix);
	//�v���W�F�N�V�����s��̓]���B
	pEffect->SetMatrix("g_projectionMatrix", projMatrix);
	//��]�s���]���B
	pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
	//���C�g�̌�����]���B
	pEffect->SetVectorArray("g_diffuseLightDirection", light->GetLightDirection(), light->GetLightNum());
	////���C�g�̃J���[��]���B
	pEffect->SetVectorArray("g_diffuseLightColor", light->GetLightColor(), light->GetLightNum());
	////������ݒ�B
	pEffect->SetVector("g_ambientLight", &light->GetambientLight());
	//�e�̃t���O��]���B
	//Stage�Ńt���O��TRUE�ɂ��Ă���
	pEffect->SetInt("g_ShadowReceiverFlag", ShadowReceiverFlag);
	//���C�g�r���[�v���W�F�N�V�����s��̓]���B
	pEffect->SetMatrix("g_mLVP", &LVP);
	//�r���[�v���W�F�N�V�����B
	pEffect->SetMatrix("g_mViewProj", &viewProj);
	//���_�B
	pEffect->SetVector("vEyePos", &(D3DXVECTOR4)g_stage->GetCamera()->GetEyePt());

	//�t���l���Z�b�g�t���O�B
	pEffect->SetInt("hureneruflg", hureneruflg);

	//�e��`�悵�Ă��郌���_�[�^�[�Q�b�g�̃e�N�X�`�����擾�B
	if (ShadowReceiverFlag == TRUE)
	{
		pEffect->SetBool("g_Ground", Ground);
		pEffect->SetTexture("g_shadowTexture", g_shadow);
		pEffect->SetTexture("g_shadowUnityTexture", g_Unity);
	}
	//���ʂ̒萔���W�X�^��ݒ�
	{
		//���C�g
		pEffect->SetValue(
			"g_light",
			light,
			sizeof(CLight)
			);
		if (isNormalMap == true)
		{
			if (normal != NULL)
			{
				//�@���}�b�v������ꍇ
				pEffect->SetTexture("g_normalTexture", normal);
				pEffect->SetInt("g_hasNormalMap", isNormalMap);
			}
		}
		else
		{
			//�@���}�b�v���Ȃ��ꍇ
			pEffect->SetTexture("g_normalTexture", NULL);
			pEffect->SetInt("g_hasNormalMap", isNormalMap);
		}
		if (isSpecularMap == true)
		{
			if (specularMap != NULL) {
				//�X�y�L�����}�b�v������̂ŁA�V�F�[�_�[�ɓ]������B
				pEffect->SetTexture("g_specularTexture", specularMap);
				//�X�y�L�����}�b�v�̂���A�Ȃ��̃t���O��true�ɂ���B
				pEffect->SetInt("g_isHasSpecularMap", isSpecularMap);
			}
		}
		else 
		{
			//�X�y�L�����}�b�v�̂���A�Ȃ��̃t���O��false�ɂ���B
			pEffect->SetTexture("g_specularTexture", NULL);
			pEffect->SetInt("g_isHasSpecularMap", isSpecularMap);
		}

		if (pMeshContainer->pSkinInfo != NULL)
		{
			//�X�L�����L��B
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
				// �f�B�t���[�Y�e�N�X�`���B
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				// �{�[�����B
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
	mesh = pMeshContainer->MeshData.pMesh;
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
	pEffect(nullptr),
	mesh(nullptr)
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
}
void SkinModel::UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	D3DXMATRIX mTrans, mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

	worldMatrix = mScale * rotationMatrix * mTrans;

	if (skinModelData) {
		skinModelData->UpdateBoneMatrix(worldMatrix);	//�{�[���s����X�V�B
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
* @brief	�擪�̃��b�V�����擾�B
*/
LPD3DXMESH SkinModel::GetOrgMeshFirst() const
{
	return skinModelData->GetOrgMeshFirst();
}

/*!
* @brief	�I���W�i�����b�V�����擾�B
*/
LPD3DXMESH SkinModel::GetOrgMesh(LPD3DXFRAME frame) const
{
	return skinModelData->GetOrgMesh(frame);
}

//���[�t�B���O�����̎��s�B
//morphTarget	���[�t�^�[�Q�b�g
//rate ���[�t�B���O���[�g�B
void SkinModel::Morphing(SkinModel* morphTargetA, SkinModel* morphTargetB, float rate)
{
	//���[�t�^�[�Q�b�gA�̃��b�V�����擾�B
	LPD3DXMESH targetMesh_A = morphTargetA->GetOrgMeshFirst();
	//���[�t�^�[�Q�b�gA�̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_A;
	targetMesh_A->GetVertexBuffer(&targetVertexBuffer_A);
	//���_�o�b�t�@�̒�`���擾����B
	D3DVERTEXBUFFER_DESC desc;
	targetVertexBuffer_A->GetDesc(&desc);
	//���_�X�g���C�h���v�Z����B
	int stride = desc.Size / targetMesh_A->GetNumVertices();

	//���[�t�^�[�Q�b�gB�̃��b�V�����擾����B
	LPD3DXMESH targetMesh_B = morphTargetB->GetOrgMeshFirst();
	//���[�t�^�[�Q�b�gB�̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_B;
	targetMesh_B->GetVertexBuffer(&targetVertexBuffer_B);

	//�����̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	GetMesh()->GetVertexBuffer(&vertexBuffer);
	D3DXVECTOR3* vertexPos;
	D3DXVECTOR3* targetVertexPos_A;
	D3DXVECTOR3* targetVertexPos_B;
	//���_�o�b�t�@�����b�N�B
	vertexBuffer->Lock(0, desc.Size, (void**)&vertexPos, D3DLOCK_DISCARD);
	targetVertexBuffer_A->Lock(0, desc.Size, (void**)&targetVertexPos_A, D3DLOCK_DISCARD);
	targetVertexBuffer_B->Lock(0, desc.Size, (void**)&targetVertexPos_B, D3DLOCK_DISCARD);
	for (int vertNo = 0; vertNo < targetMesh_A->GetNumVertices(); vertNo++) {
		///////////////////////////////////////////////////////////////////
		//�����ɒ��_���[�t�̏������L�q����B
		///////////////////////////////////////////////////////////////////
		*vertexPos = *targetVertexPos_A * (1.0f - rate) + *targetVertexPos_B * rate;

		//���̒��_�ցB
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
	//���_�o�b�t�@���A�����b�N�B
	vertexBuffer->Unlock();
	targetVertexBuffer_A->Unlock();
	targetVertexBuffer_B->Unlock();
	vertexBuffer->Release();
	targetVertexBuffer_A->Release();
	targetVertexBuffer_B->Release();
}