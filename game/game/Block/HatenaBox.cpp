#include "stdafx.h"
#include "HatenaBox.h"
#include "Map\stage.h"

SCollisionInfo collisionInfoTableHatena[] = {
#include "Collision\Collision_hatenabox1.h"
};

//コンストラクタ
CHatenaBox::CHatenaBox()
{
	//初期化。
	D3DXMatrixIdentity(&mWorld);
	position = { 8.0f, 4.0f, 0.0f };
	
}
//デストラクタ
CHatenaBox::~CHatenaBox()
{
	Release();
}
//初期化。
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateCollision();
	AddRigidBody();

	model.Init(pd3dDevice, "Asset/model/hatena_box.x");
	model.SetShadowReceiverFlag(false);

	state = HatenaState::nohit;
}
//更新。
void CHatenaBox::Update()
{	
	if (state == HatenaState::hit)
	{
		model.SetTexture("Asset/model/kara.png",false);
		state = HatenaState::nohit;
	}
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
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
//開放。
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
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
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

void CHatenaBox::AddRigidBody()//ワールドに追加。
{
	if (!isAddCollision){
		isAddCollision = true;
		g_physicsWorld->AddRigidBody(rigidBodyHatena);
	}
}
