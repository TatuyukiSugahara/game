#include "stdafx.h"
#include "Pipe.h"
#include "PipeChip.h"
#include "Stage.h"


using namespace std;

//ステージ１
//土管チップの配置情報のテーブル。
SPipeChipLocInfo pipeChipLocInfoTable[] = {
#include "locationPipe.h"
};
//あたり判定
SCollisionInfoPipe collisionInfoTablepipe[] = {
#include "Collision_Pipe.h"
};

//ステージ２
//土管チップの配置情報のテーブル。
SPipeChipLocInfo pipeChipLocInfoTable2[] = {
#include "locationPipe_2.h"
};
//あたり判定
SCollisionInfoPipe collisionInfoTablpipe2[] = {
#include "Collision_Pipe2.h"
};

CPipe::CPipe()
{
	nextPos = CConst::Vec3Zero;
	isPipe = false;
	memset(pipeboxShape, NULL, sizeof(pipeboxShape));
	memset(rigidBodypipe, NULL, sizeof(rigidBodypipe));
	myMotionState = NULL;
	pipeChipTable = NULL;
	collisionTablpipe = NULL;
}
CPipe::~CPipe()
{
	for (auto& pipechip : pipeChipList){
		delete pipechip;
	}
	for (auto& pipeBox : pipeboxShape){
		delete pipeBox;
	}
	for (auto& rb : rigidBodypipe){
		delete rb;
	}
	delete myMotionState;
}
void CPipe::Init()
{
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		pipeChipTable = pipeChipLocInfoTable;
		collisionTablpipe = collisionInfoTablepipe;
		tableSize = sizeof(pipeChipLocInfoTable) / sizeof(pipeChipLocInfoTable[0]);
		arraySize = ARRAYSIZE(collisionInfoTablepipe);
		break;
	case CSceneManager::StageNumber::Stage2:
		pipeChipTable = pipeChipLocInfoTable2;
		collisionTablpipe = collisionInfoTablpipe2;
		tableSize = sizeof(pipeChipLocInfoTable2) / sizeof(pipeChipLocInfoTable2[0]);
		arraySize = ARRAYSIZE(collisionInfoTablpipe2);
		break;
	}

	//配置情報からマップを構築
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CPipeChip* pipeChip = new CPipeChip;
		pipeChip->SetPos(pipeChipTable[a].pos);
		pipeChip->SetRot(pipeChipTable[a].rotation);
		pipeChip->SetScale(pipeChipTable[a].scale);
		pipeChip->Init();
		pipeChipList.push_back(pipeChip);
	}
	
	CreateCollision();
	AddRigidBody(arraySize);

}
void CPipe::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Update();
	}
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		PipeMove(6, 7, 9);
		PipeMove(8, 7, 11);
		break;
	case CSceneManager::StageNumber::Stage2:
		PipeMove(0, 1, 0);
		PipeMove(2, 3, 2);
		PipeMove(4, 5, 4);
		break;
	}

	InPipe();
}

void CPipe::Render(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Render(viewMatrix,
			projMatrix,
			isDrawToShadowMap);
	}
}

void CPipe::CreateCollision()
{
	if (arraySize >= MAXCOLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfoPipe& collision = collisionTablpipe[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			pipeboxShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, pipeboxShape[i], btVector3(0, 0, 0));
			rigidBodypipe[i] = new btRigidBody(rbInfo);
		}
	}
}

void CPipe::AddRigidBody(int arraySize)//ワールドに追加。
{
	if (!isAddCollision){
		isAddCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_physicsWorld->AddRigidBody(rigidBodypipe[i]);
		}
	}
}

void CPipe::RemoveRigidBody(int arraySize)//ワールドから削除
{
	if (isAddCollision){
		isAddCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (rigidBodypipe[i] != NULL)
				g_physicsWorld->RemoveRigidBody(rigidBodypipe[i]);
		}
	}
}

//入った時の処理
void CPipe::InPipe()
{
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
			AddRigidBody(arraySize);
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

//移動処理
void CPipe::PipeMove(int now, int next, int pipenum)
{
	if (g_stage->GetPlayer()->GetcharacterController().getCollisionObj() == rigidBodypipe[now]
		&& g_stage->GetPlayer()->GetcharacterController().IsOnGround() == true
		)
	{
		D3DXVECTOR3 toPos = pipeChipTable[pipenum].pos - g_stage->GetPlayer()->GetPos();
		float dir = D3DXVec3Length(&toPos);
		D3DXVec3Normalize(&toPos, &toPos);
		g_stage->GetPlayer()->SetMoveSpeed(toPos * 2.0f);
		if (fabs(dir) < 2.3f)
		{
			isPipe = true;
			RemoveRigidBody(arraySize);
			sePipe.reset(new CSoundSource);
			sePipe->Init("Asset/Sound/Pipe.wav");
			sePipe->Play(false);
			nextPos = D3DXVECTOR3(collisionTablpipe[next].pos.x
				, collisionTablpipe[next].pos.y - 0.5f
				, collisionTablpipe[next].pos.z);
		}
	}
}