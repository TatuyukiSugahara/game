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
}
CPipe::~CPipe()
{
	for (auto& pipechip : pipeChipList){
		delete pipechip;
	}
}
void CPipe::Init(LPDIRECT3DDEVICE9 pd3dDevice)
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
		pipeChip->Init(pipeChipLocInfoTable[a].modelName, pd3dDevice);
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
	if (/*g_stage->GetPlayer()->GetIsIntersect().getCollisionObj()*/g_stage->GetPlayer()->GetcharacterController().getCollisionObj() == m_rigidBody2Dpipe[4]
		&& /*g_stage->GetPlayer()->GetIsIntersect().GetGround()*/g_stage->GetPlayer()->GetcharacterController().IsOnGround()
		&& g_pad.IsTrigger(enButtonDown))
	{
	
			nextPos = D3DXVECTOR3(collisionInfoTable2Dpipe[12].pos.x
				, collisionInfoTable2Dpipe[12].pos.y - g_stage->GetPlayer()->GetPos().y
				, collisionInfoTable2Dpipe[12].pos.z);
			isPipe = true;
			Remove2DRigidBody(arraySize);
			CSoundSource* SEPipe = new CSoundSource;
			SEPipe->Init("Asset/Sound/Pipe.wav");
			SEPipe->Play(false);
			SEPipe->SetVolume(0.25f);
	}
	if (/*g_stage->GetPlayer()->GetIsIntersect().getCollisionObj()*/g_stage->GetPlayer()->GetcharacterController().getCollisionObj() == m_rigidBody2Dpipe[13]
		&& /*g_stage->GetPlayer()->GetIsIntersect().GetGround()*/g_stage->GetPlayer()->GetcharacterController().IsOnGround()
		&& g_pad.IsTrigger(enButtonDown))
	{
		nextPos = D3DXVECTOR3(collisionInfoTable2Dpipe[5].pos.x
			, collisionInfoTable2Dpipe[5].pos.y + collisionInfoTable2Dpipe[5].pos.y
			, collisionInfoTable2Dpipe[5].pos.z);
		isPipe = true;
		Remove2DRigidBody(arraySize);
		CSoundSource* SEPipe = new CSoundSource;
		SEPipe->Init("Asset/Sound/Pipe.wav");
		SEPipe->SetVolume(2.0f);
		SEPipe->Play(false);
	}

	if (isPipe == true)
	{
		count++;
		if (count >= 30)
		{
			g_stage->GetPlayer()->SetPosition(nextPos);
			isPipe = false;
			Add2DRigidBody(arraySize);
			count = 0;
		}
	}

}
void CPipe::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Render(
			pd3dDevice,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight
			);
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
			//g_physicsWorld.AddRigidBody(m_rigidBody2Dpipe[i]);

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
			g_physicsWorld.AddRigidBody(m_rigidBody2Dpipe[i]);
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
				g_physicsWorld.RemoveRigidBody(m_rigidBody2Dpipe[i]);
		}
	}
}