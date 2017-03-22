#include "stdafx.h"
#include "Bird.h"
#include "BirdChip.h"
#include "Stage.h"

using namespace std;

//鳥チップの配置情報のテーブル。
SBirdChipLocInfo birdChipListTable[] = {
	#include "LocationBird.h"
};

//鳥チップの配置情報のテーブル。
SBirdChipLocInfo birdChipListTable2[] = {
#include "LocationBird2.h"
};

CBird::CBird()
{
	birdChipLoc = NULL;
}


CBird::~CBird()
{
	for (auto& birdchip : birdChipList){
		delete birdchip;
	}
}

//初期化。
void CBird::Init()
{
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		birdChipLoc = birdChipListTable;
		tableSize = sizeof(birdChipListTable) / sizeof(birdChipListTable[0]);
		break;
	case CSceneManager::StageNumber::Stage2:
		birdChipLoc = birdChipListTable2;
		tableSize = sizeof(birdChipListTable2) / sizeof(birdChipListTable2[0]);
		break;
	}

	//配置情報から鳥を構築
	for (int a = 0; a < tableSize; a++)
	{
		//鳥チップを生成
		CBirdChip* birdchip = new CBirdChip;
		birdchip->SetPosition(birdChipLoc[a].pos);
		birdchip->Init(birdChipLoc[a].modelName, g_pd3dDevice);
		birdChipList.push_back(birdchip);
	}
}
//更新。
void CBird::Update()
{
	tableSize = sizeof(birdChipListTable) / sizeof(birdChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		birdChipList[a]->Update();
	}
}
//描画。
void CBird::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		birdChipList[a]->Render(viewMatrix, projMatrix,isDrawToShadowMap);
	}
}
