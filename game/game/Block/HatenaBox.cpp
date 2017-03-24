#include "stdafx.h"
#include "HatenaBox.h"
#include "Map\stage.h"

SCollisionInfo collisionInfoTableHatena[] = {
#include "Collision\Collision_hatenabox1.h"
};

//�R���X�g���N�^
CHatenaBox::CHatenaBox()
{
	//�������B
	D3DXMatrixIdentity(&mWorld);
	position = { 8.0f, 4.0f, 0.0f };
	
}
//�f�X�g���N�^
CHatenaBox::~CHatenaBox()
{
	Release();
}
//�������B
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateCollision();
	AddRigidBody();

	model.Init(pd3dDevice, "Asset/model/hatena_box.x");
	model.SetShadowReceiverFlag(false);

	state = HatenaState::nohit;
}
//�X�V�B
void CHatenaBox::Update()
{	
	if (state == HatenaState::hit)
	{
		model.SetTexture("Asset/model/kara.png",false);
		state = HatenaState::nohit;
	}
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CHatenaBox::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	model.Render(
		pd3dDevice,
		mWorld,
		mRotation,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight,
		false
		);
}
//�J���B
void CHatenaBox::Release()
{
	model.Release();
	if (rigidBodyHatena){
	
		rigidBodyHatena = NULL;
	}
}

void CHatenaBox::CreateCollision()
{
	SCollisionInfo& collision = *collisionInfoTableHatena;
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			hatenaboxShape = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, hatenaboxShape, btVector3(0, 0, 0));
			rigidBodyHatena = new btRigidBody(rbInfo);

		}
	
}

void CHatenaBox::AddRigidBody()//���[���h�ɒǉ��B
{
	if (!isAddCollision){
		isAddCollision = true;
		g_physicsWorld->AddRigidBody(rigidBodyHatena);
	}
}
