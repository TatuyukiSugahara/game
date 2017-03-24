#include "stdafx.h"
#include "NoBlock.h"
#include "Map\stage.h"

SCollisionInfo collisionInfoTablenoblock[] = {
#include "Collision\Collision_noblockbox1.h"
};

//�R���X�g���N�^
CNoBlock::CNoBlock()
{
	//�������B
	position = D3DXVECTOR3(191.0f, 4.5f, 0.0f);
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;

}
//�f�X�g���N�^
CNoBlock::~CNoBlock()
{
	delete noblockboxShape;
	delete rigidBodynoblock;
	delete myMotionState;
}
//�������B
void CNoBlock::Init()
{
	//���C�g���������B
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
//�X�V�B
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
//�`��B
void CNoBlock::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	if (state == NoblockState::hit)
	{
		skinModel.Render(&viewMatrix, &projMatrix, false);
	}
}
//�J���B
void CNoBlock::Release()
{
	
}

void CNoBlock::CreateCollision()
{
	SCollisionInfo& collision = *collisionInfoTablenoblock;
	//�����ō��̂Ƃ���o�^����B
	//���̂��������B
	{
		//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
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

void CNoBlock::AddRigidBody()//���[���h�ɒǉ��B
{
	if (!isAddCollision){
		isAddCollision = true;
		g_physicsWorld->AddRigidBody(rigidBodynoblock);
	}
}
