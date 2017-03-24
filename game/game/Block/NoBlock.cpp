#include "stdafx.h"
#include "NoBlock.h"
#include "Map\stage.h"

SCollisionInfo collisionInfoTablenoblock[] = {
#include "Collision\Collision_noblockbox1.h"
};

//コンストラクタ
CNoBlock::CNoBlock()
{
	//初期化。
	position = D3DXVECTOR3(191.0f, 4.5f, 0.0f);
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;

}
//デストラクタ
CNoBlock::~CNoBlock()
{
	delete noblockboxShape;
	delete rigidBodynoblock;
	delete myMotionState;
}
//初期化。
void CNoBlock::Init()
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

	modelData.LoadModelData("Asset/model/karabox.x", &animation);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	skinModel.SetShadowReceiverFlag(false);

	state = NoblockState::nohit;

	CreateCollision();
	AddRigidBody();
}
//更新。
void CNoBlock::Update()
{
	if (state == NoblockState::hit)
	{
		skinModel.UpdateWorldMatrix(position, rotation, scale);
	}
	else if (state == NoblockState::nohit)
	{
		if (Getnoblock() == g_stage->GetPlayer()->GetcharacterController().getCollisionObj()
			&& g_stage->GetPlayer()->GetcharacterController().IsCeiling() == true)
		{
			state = NoblockState::hit;
		}
	}
}
//描画。
void CNoBlock::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	if (state == NoblockState::hit)
	{
		skinModel.Render(&viewMatrix, &projMatrix, false);
	}
}
//開放。
void CNoBlock::Release()
{
	
}

void CNoBlock::CreateCollision()
{
	SCollisionInfo& collision = *collisionInfoTablenoblock;
	//ここで剛体とかを登録する。
	//剛体を初期化。
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		noblockboxShape = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, noblockboxShape, btVector3(0, 0, 0));
		rigidBodynoblock = new btRigidBody(rbInfo);

	}

}

void CNoBlock::AddRigidBody()//ワールドに追加。
{
	if (!isAddCollision){
		isAddCollision = true;
		g_physicsWorld->AddRigidBody(rigidBodynoblock);
	}
}
