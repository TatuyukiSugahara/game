#include "stdafx.h"
#include "NBlockChip.h"
#include "Stage.h"

CNBlockChip::CNBlockChip()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXMatrixIdentity(&mWorld);
	blockLost = false;
	animState = BlockOff;
}

CNBlockChip::~CNBlockChip()
{
	delete m_blockboxShape;
	delete m_myMotionState;
	if (m_rigidBody3Dblock){
		delete m_rigidBody3Dblock;
	}
	if (m_rigidBody2Dblock){
		delete m_rigidBody2Dblock;
	}
	if (normalMap != NULL)
	{
		normalMap->Release();
	}
}
void CNBlockChip::Init()
{
	//ノーマルマップロード
	HRESULT hr = D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Asset/model/block_NormalMap.png",
		&normalMap);
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャのロードに失敗しました。指定したパスが正しいか確認してください。", "エラー", MB_OK);
	}
	if (normalMap != NULL) {
		//法線マップの読み込みが成功したので、CSkinModelに法線マップを設定する。
		skinmodel.SetNormalMap(normalMap);
	}

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	modelData.LoadModelData("Asset/model/block.x", &animation);
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0);
	animation.SetAnimationLoopFlag(1, false);
	skinmodel.SetShadowReceiverFlag(true);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetGround(true);
	skinmodel.SetNormalMap(true);
	skinmodel.SetSpecularMap(false);

	CreateCollision2D();
	Add2DRigidBody();

	param.texturePath = "Asset/model/block.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.3f;
	param.life = 1.0f;
	param.gravity = D3DXVECTOR3(0.0f, -0.2f, 0.0f);
	param.initSpeed = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	param.pos = position;
	parflag = false;
	parTime = 0;
	CParticleEmitter* particleEmitter = new CParticleEmitter;
	particleEmitter->Init(param);
	particleEmitterList.push_back(particleEmitter);
}

void CNBlockChip::Update()
{
	if (blockLost == true)//ブロック壊された
	{
		Remove2DRigidBody();
		if (animState != BlockOn)
		{
			animation.PlayAnimation(1);
			animation.SetAnimationSpeedRate(2.5f);
			animState = AnimState::BlockOn;
		}

		if (parflag == true)
		{
			if (MAXPAR >= parTime)
			{
				parTime++;
				for (auto p : particleEmitterList)
				{
					p->Update();
				}
			}
			else
			{
				parflag = false;
				for (auto p : particleEmitterList)
				{
					delete(p);
				}
				particleEmitterList.clear();
			}
		}
	}
	animation.Update(1.0f / 60.0f);
	
}

void CNBlockChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (isDrawToShadowMap == true)
	{
		skinmodel.UpdateWorldMatrix(position - D3DXVECTOR3(0.0f, 1.5f,0.0f), rotation, scale);
	}
	else
	{
		skinmodel.UpdateWorldMatrix(position, rotation, scale);
	}
	if (MAXPAR >= parTime)
	{
		skinmodel.Draw(&viewMatrix, &projMatrix, isDrawToShadowMap);
	}

	if (blockLost == true)
	{
		if (MAXPAR >= parTime)
		{
			for (auto p : particleEmitterList)
			{
				p->Render(g_stage->GetCamera()->GetViewMatrix(), g_stage->GetCamera()->GetProjectionMatrix());
			}
		}
	}
}

void CNBlockChip::CreateCollision2D()
{
	//ここで剛体とかを登録する。
	//剛体を初期化。
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		m_blockboxShape = new btBoxShape(btVector3(scale.x*0.5f, scale.y*0.5f, scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(position.x, position.y, position.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_blockboxShape, btVector3(0, 0, 0));
		m_rigidBody2Dblock = new btRigidBody(rbInfo);
	}

}

void CNBlockChip::Add2DRigidBody()//ワールドに追加。
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		g_physicsWorld->AddRigidBody(m_rigidBody2Dblock);
		
	}
}

void CNBlockChip::Remove2DRigidBody()
{
	if (m_rigidBody2Dblock != NULL)
	{
		g_physicsWorld->RemoveRigidBody(m_rigidBody2Dblock);
	}
}