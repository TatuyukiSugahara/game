#include "stdafx.h"
#include "HatenaBox.h"
#include "stage.h"

SCollisionInfo collisionInfoTable2Dhatena[] = {
#include "Collision2D_hatenabox1.h"
};

//�R���X�g���N�^
CHatenaBox::CHatenaBox()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 8.0f;
	position.y = 4.0f;
	position.z = 0.0f;
	
}
//�f�X�g���N�^
CHatenaBox::~CHatenaBox()
{
}
//�������B
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateCollision2D();
	Add2DRigidBody();

	model.Init(pd3dDevice, "hatena_box.x");

	Item = false;
}
//�X�V�B
void CHatenaBox::Update()
{	
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
		numDiffuseLight
		);
}
//�J���B
void CHatenaBox::Release()
{
	model.Release();
}

void CHatenaBox::CreateCollision2D()
{
	SCollisionInfo& collision = *collisionInfoTable2Dhatena;
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			m_hatenaboxShape = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_hatenaboxShape, btVector3(0, 0, 0));
			m_rigidBody2Dhatena = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);

		}
	
}

void CHatenaBox::Add2DRigidBody()//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		g_bulletPhysics.AddRigidBody(m_rigidBody2Dhatena);
	}
}
