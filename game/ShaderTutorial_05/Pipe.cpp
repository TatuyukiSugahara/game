#include "stdafx.h"
#include "Pipe.h"
#include "PipeChip.h"
#include "Stage.h"


using namespace std;


//土管チップの配置情報のテーブル。
SPipeChipLocInfo pipeChipLocInfoTable[] = {
#include "locationPipe.h"
};
//あたり判定
SCollisionInfo collisionInfoTable2Dpipe[] = {
#include "Collision2D_Pipe.h"
};

CPipe::CPipe()
{
	nextPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isPipe = false;
	memset(m_pipeboxShape, NULL, sizeof(m_pipeboxShape));
	memset(m_rigidBody3Dpipe, NULL, sizeof(m_rigidBody3Dpipe));
	memset(m_rigidBody2Dpipe, NULL, sizeof(m_rigidBody2Dpipe));
	m_myMotionState = NULL;
}
CPipe::~CPipe()
{
	for (auto& pipechip : pipeChipList){
		delete pipechip;
	}
	for (auto& pipeBox : m_pipeboxShape){
		delete pipeBox;
	}
	for (auto& rb : m_rigidBody3Dpipe){
		delete rb;
	}
	for (auto& rb : m_rigidBody2Dpipe){
		delete rb;
	}
	delete m_myMotionState;
}
void CPipe::Init()
{
	//配置情報からマップを構築
	tableSize = sizeof(pipeChipLocInfoTable) / sizeof(pipeChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CPipeChip* pipeChip = new CPipeChip;
		pipeChip->SetPos(pipeChipLocInfoTable[a].pos);
		pipeChip->SetRot(pipeChipLocInfoTable[a].rotation);
		pipeChip->SetScale(pipeChipLocInfoTable[a].scale);
		pipeChip->Init();
		pipeChipList.push_back(pipeChip);
	}
	arraySize = ARRAYSIZE(collisionInfoTable2Dpipe);
	CreateCollision2D();
	Add2DRigidBody(arraySize);

}
void CPipe::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Update();
	}

	PipeMove(6, 7, 9);
	PipeMove(8, 7, 11);
	

	if (isPipe == true)
	{
		count++;
		static D3DXVECTOR3 scale = g_stage->GetPlayer()->GetScale();
		if (count <= 30)
		{
			g_stage->GetPlayer()->SubScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
		}
		if (count == 30)
		{
			g_stage->GetPlayer()->SetPosition(nextPos);
			Add2DRigidBody(arraySize);
		}
		if (count <= 60 && count >= 30)
		{
			g_stage->GetPlayer()->AddScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
		}
		if (count >= 60)
		{
			g_stage->GetPlayer()->SetScale(scale);
			isPipe = false;
			count = 0;
		}
	}

}
void CPipe::Render()
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Render();
	}
}

void CPipe::CreateCollision2D()
{
	if (arraySize >= MAXCOLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable2Dpipe[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			m_pipeboxShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_pipeboxShape[i], btVector3(0, 0, 0));
			m_rigidBody2Dpipe[i] = new btRigidBody(rbInfo);

			//ワールドに追加。
			//g_physicsWorld->AddRigidBody(m_rigidBody2Dpipe[i]);

		}
	}
}

void CPipe::Add2DRigidBody(int arraySize)//ワールドに追加。
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_physicsWorld->AddRigidBody(m_rigidBody2Dpipe[i]);
		}
	}
}

void CPipe::Remove2DRigidBody(int arraySize)//ワールドから削除
{
	if (m_isAdd2DCollision){
		m_isAdd2DCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (m_rigidBody2Dpipe[i] != NULL)
				g_physicsWorld->RemoveRigidBody(m_rigidBody2Dpipe[i]);
		}
	}
}

void CPipe::PipeMove(int now, int next, int pipenum)
{
	if (g_stage->GetPlayer()->GetcharacterController().getCollisionObj() == m_rigidBody2Dpipe[now]
		&& g_stage->GetPlayer()->GetcharacterController().IsOnGround() == true
		)
	{
		D3DXVECTOR3 toPos = pipeChipLocInfoTable[pipenum].pos - g_stage->GetPlayer()->GetPos();
		float dir = D3DXVec3Length(&toPos);
		D3DXVec3Normalize(&toPos, &toPos);
		g_stage->GetPlayer()->SetMoveSpeed(toPos * 2.0f);
		if (fabs(dir) < 2.3f)
		{
			isPipe = true;
			Remove2DRigidBody(arraySize);
			CSoundSource* SEPipe = new CSoundSource;
			SEPipe->Init("Asset/Sound/Pipe.wav");
			SEPipe->Play(false);
			SEPipe->SetVolume(0.25f);
			nextPos = D3DXVECTOR3(collisionInfoTable2Dpipe[next].pos.x
				, collisionInfoTable2Dpipe[next].pos.y - 0.5f
				, collisionInfoTable2Dpipe[next].pos.z);
		}
	}
}