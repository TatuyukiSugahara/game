#include "stdafx.h"
#include "NBlock.h"
#include "stage.h"
#include "Sound\SoundSource.h"

SCollisionInfo collisionInfoTable2Dblock[] = {
#include "Collision2D_blockbox1.h"
};

//�R���X�g���N�^
CNBlock::CNBlock()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 14.0f;
	position.y = 4.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CNBlock::~CNBlock()
{
}
//�������B
void CNBlock::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateCollision2D();
	Add2DRigidBody();
	model.Init(pd3dDevice, "Asset/model/block.x");
	state = yes;

	param.texturePath = "Asset/model/block.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.5f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	param.pos = position;

	parflag = false;
	parTime = 0; 
	CParticleEmitter* particleEmitter = new CParticleEmitter;
	particleEmitter->Init(param);
	particleEmitterList.push_back(particleEmitter);
}
//�X�V�B
void CNBlock::Update()
{
	if (state == no)//�u���b�N�󂳂ꂽ
	{
		Remove2DRigidBody();
		
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
	else
	{
		//���[���h�s��̍X�V�B
		D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
	}

	
}
//�`��B
void CNBlock::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	if (state == yes)		//�o�����Ă���Ȃ�
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
	else
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
//�J���B
void CNBlock::Release()
{
	model.Release();
}

void CNBlock::CreateCollision2D()
{
	SCollisionInfo& collision = *collisionInfoTable2Dblock;
	//�����ō��̂Ƃ���o�^����B
	//���̂��������B
	{
		//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
		m_blockboxShape = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_blockboxShape, btVector3(0, 0, 0));
		m_rigidBody2Dblock = new btRigidBody(rbInfo);
	}

}

void CNBlock::Add2DRigidBody()//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		g_bulletPhysics.AddRigidBody(m_rigidBody2Dblock);
	}
}

void CNBlock::Remove2DRigidBody()
{
	if (m_rigidBody2Dblock != NULL)
	{
		g_bulletPhysics.RemoveRigidBody(m_rigidBody2Dblock);
	}
}