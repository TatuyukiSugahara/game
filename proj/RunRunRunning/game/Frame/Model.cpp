#include "stdafx.h"
#include "Model.h"
#include "Map\Stage.h"

//�R���X�g���N�^
Model::Model()
{
	mesh = NULL;
	textures = NULL;
	numMaterial = 0;
	effect = NULL;
	ShadowReceiverFlag = false;
}
//�f�X�g���N�^
Model::~Model()
{
	Release();
}
//�������B
void Model::Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName)
{
	Release();
	//X�t�@�C�������[�h�B
	LPD3DXBUFFER pD3DXMtrlBuffer;
	//X�t�@�C���̃��[�h�B
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	//�@�������݂��邩���ׂ�B
	if ((mesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		//�@�����Ȃ��̂ō쐬����B
		ID3DXMesh* pTempMesh = NULL;

		mesh->CloneMeshFVF(mesh->GetOptions(),
			mesh->GetFVF() | D3DFVF_NORMAL, g_pd3dDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		mesh->Release();
		mesh = pTempMesh;

	}

	// �}�e���A���o�b�t�@���擾�B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//�e�N�X�`�������[�h�B
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	tex = new CTexture[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		char* baseDir = "Asset/model/";
		char filePath[64];
		strcpy(filePath, baseDir);
		strcat(filePath, d3dxMaterials[i].pTextureFilename);
		textures[i] = NULL;
		tex[i].SetTextureDX(NULL);
		//�e�N�X�`�����쐬����B
		D3DXCreateTextureFromFileA(pd3dDevice,
			filePath,
			&textures[i]);
		tex[i].SetTextureDX(textures[i]);
	}
	// �}�e���A���o�b�t�@������B
	pD3DXMtrlBuffer->Release();

	//�V�F�[�_�[���R���p�C���B
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//�V�F�[�_�[���R���p�C���B
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,
		"Asset/Shader/basic.fx",
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
//�`��B
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
		mWVP = worldMatrix * g_stage->GetShadow()->Getlvpmatrix();
		//���_�ݒ�
		effect->SetMatrix("g_mWVP", &mWVP);

		

		for (DWORD i = 0; i < numMaterial; i++)
		{
			effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
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

		//�萔���W�X�^�ɐݒ肷��J���[�B
		D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
		//���[���h�s��̓]���B
		effect->SetMatrix("g_worldMatrix", &worldMatrix);
		//�r���[�s��̓]���B
		effect->SetMatrix("g_viewMatrix", &viewMatrix);			//�r���[�s���]���B

		effect->SetMatrix("g_projectionMatrix", &projMatrix);	//�v���W�F�N�V�����s��̓]���B

		effect->SetMatrix("g_rotationMatrix", &rotationMatrix);		//��]�s���]���B
		//���C�g�̌�����]���B
		effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
		//���C�g�̃J���[��]���B
		effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
		//������ݒ�B
		effect->SetVector("g_ambientLight", &ambientLight);
		//���_�ݒ�
		effect->SetVector("vEyePos", &(D3DXVECTOR4)g_stage->GetCamera()->GetEyePt());

		effect->SetInt("g_ShadowReceiverFlag", ShadowReceiverFlag);//�e�t���O
		
		effect->SetTexture("g_shadowTexture", g_shadow);//�e
		effect->SetMatrix("g_lightVPMatrix", &g_stage->GetShadow()->Getlvpmatrix());
		
		for (DWORD i = 0; i < numMaterial; i++)
		{
			effect->SetTexture("g_diffuseTexture", tex[i].GetTextureDX());
			effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
			// Draw the mesh subset
			mesh->DrawSubset(i);
		}
		
		effect->EndPass();
		effect->End();
	}
	
}
//�J���B
void Model::Release()
{
	//���b�V�����J���B
	if (mesh != NULL) {
		mesh->Release();
		mesh = NULL;
	}
	//�e�N�X�`�����J���B
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
	//�e�N�X�`�����J���B
	if (tex != NULL) {
		for (unsigned int i = 0; i < numMaterial; i++) {
			if (tex[i].GetTextureDX() != NULL) {
				tex[i].SetTextureDX(NULL);
			}
		}
		delete[] tex;
		tex = NULL;
	}
	//�G�t�F�N�g���J���B
	if (effect != NULL) {
		effect->Release();
		effect = NULL;
	}
}