#include "stdafx.h"
#include "Saboten.h"
#include "stage.h"

//SCollisionInfo collisionInfoTable2Dsabo[] = {
//#include "Collision2D_blocksabo.h"
//};

//�R���X�g���N�^
CSaboten::CSaboten()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 39.0f;
	position.y = 1.25f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CSaboten::~CSaboten()
{
}
//�������B
void CSaboten::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	/*CreateCollision2D();
	Add2DRigidBody();*/
	model.Init(pd3dDevice, "Asset/model/sabo.x");
}
//�X�V�B
void CSaboten::Update()
{
	BOOL hit;//�q�b�g������
	FLOAT distance;	//����
	D3DXVECTOR3 dir = position - g_stage.GetPlayer()->GetPos();
	D3DXVECTOR3 pos = g_stage.GetPlayer()->GetPos();
	D3DXVec3Normalize(&dir, &dir);
	D3DXMATRIX InverseMat;
	D3DXMATRIX InverseRot;
	D3DXMatrixInverse(&InverseMat, NULL, &mWorld);
	D3DXMatrixInverse(&InverseRot, NULL, &mRotation);

	D3DXVec3TransformCoord(&pos, &pos, &InverseMat);
	D3DXVec3TransformCoord(&dir, &dir, &InverseRot);

	D3DXIntersect(model.GetMesh(), &pos,
		&dir, &hit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (hit)
	{
		if (fabs(distance) <= 0.1f)
		{
			MessageBox(NULL, "GAME OVER", 0, MB_OK);
			exit(0);
		}
	}
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CSaboten::Render(
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
void CSaboten::Release()
{
	model.Release();
}

//void CSaboten::CreateCollision2D()
//{
//	SCollisionInfo& collision = *collisionInfoTable2Dsabo;
//	//�����ō��̂Ƃ���o�^����B
//	//���̂��������B
//	{
//		//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
//		m_saboboxShape = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
//		btTransform groundTransform;
//		groundTransform.setIdentity();
//		groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
//		float mass = 0.0f;
//
//		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//		m_myMotionState = new btDefaultMotionState(groundTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_saboboxShape, btVector3(0, 0, 0));
//		m_rigidBody2Dsabo = new btRigidBody(rbInfo);
//	}
//
//}
//
//void CSaboten::Add2DRigidBody()//���[���h�ɒǉ��B
//{
//	if (!m_isAdd2DCollision){
//		m_isAdd2DCollision = true;
//		g_bulletPhysics.AddRigidBody(m_rigidBody2Dsabo);
//	}
//}
