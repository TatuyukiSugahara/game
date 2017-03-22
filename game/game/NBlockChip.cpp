#include "stdafx.h"
#include "NBlockChip.h"
#include "Stage.h"

SkinModelData*	CNBlockChip::orgSkinModelData = NULL;	//オリジナルスキンモデルデータ。

CNBlockChip::CNBlockChip()
{
	position = CConst::Vec3Zero;
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;
	blockLost = false;
	animState = AnimState::Off;
}

CNBlockChip::~CNBlockChip()
{
	delete blockboxShape;
	delete myMotionState;
	if (rigidBodyBlock){
		delete rigidBodyBlock;
	}
	/*if (orgSkinModelData)
	{
		delete orgSkinModelData; 
	}
	if (orgAnimation)
	{
		delete orgAnimation;
	}*/
}
void CNBlockChip::Init()
{
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

	if (orgSkinModelData == NULL) {
		orgSkinModelData = new SkinModelData;
		orgAnimation = new Animation;
		orgSkinModelData->LoadModelData("Asset/model/block.x", orgAnimation);
	}
	//オリジナルのモデルデータからクローンモデルを作成。
	modelData.CloneModelData(*orgSkinModelData, NULL);

	//modelData.LoadModelData("Asset/model/block.x", &animation);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	animation.PlayAnimation(0);
	animation.SetAnimationLoopFlag(1, false);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetGround(true);
	skinModel.SetNormalMap(true);
	skinModel.SetSpecularMap(false);

	CreateCollision();
	AddRigidBody();

	param.texturePath = "Asset/model/block.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.3f;
	param.life = 1.0f;
	param.gravity = D3DXVECTOR3(0.0f, -0.5f, 0.0f);
	param.initSpeed = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	param.pos = position;
	parFlag = false;
	parTime = 0;
	CParticleEmitter* particleEmitter = new CParticleEmitter;
	particleEmitter->Init(param);
	particleEmitterList.push_back(particleEmitter);
}

void CNBlockChip::Update()
{
	if (blockLost == true)//ブロック壊された
	{
		RemoveRigidBody();
		if (animState != AnimState::On)
		{
			animation.PlayAnimation(1);
			animation.SetAnimationSpeedRate(2.5f);
			animState = AnimState::On;
		}

		if (parFlag == true)
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
				parFlag = false;
				for (auto p : particleEmitterList)
				{
					delete(p);
				}
				particleEmitterList.clear();
			}
		}
	}
	animation.Update(CConst::DeltaTime);
	
}

void CNBlockChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (isDrawToShadowMap == true)
	{
		skinModel.UpdateWorldMatrix(position - D3DXVECTOR3(0.0f, 1.5f,0.0f), rotation, scale);
	}
	else
	{
		skinModel.UpdateWorldMatrix(position, rotation, scale);
	}
	if (MAXPAR >= parTime)
	{
		skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
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

void CNBlockChip::CreateCollision()
{
	//ここで剛体とかを登録する。
	//剛体を初期化。
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		blockboxShape = new btBoxShape(btVector3(scale.x*0.5f, scale.y*0.5f, scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(position.x, position.y, position.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, blockboxShape, btVector3(0, 0, 0));
		rigidBodyBlock = new btRigidBody(rbInfo);
	}

}

void CNBlockChip::AddRigidBody()//ワールドに追加。
{
	if (!isAddCollision){
		isAddCollision = true;
		g_physicsWorld->AddRigidBody(rigidBodyBlock);
		
	}
}

void CNBlockChip::RemoveRigidBody()
{
	if (rigidBodyBlock != NULL)
	{
		g_physicsWorld->RemoveRigidBody(rigidBodyBlock);
	}
}