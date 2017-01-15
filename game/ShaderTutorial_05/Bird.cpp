#include "stdafx.h"
#include "Bird.h"
#include "BirdChip.h"
#include "Stage.h"

using namespace std;

//マップチップの配置情報のテーブル。
SBirdChipLocInfo birdChipListTable[] = {
	#include "LocationBird.h"
};

CBird::CBird()
{
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
	//配置情報からマップを構築
	tableSize = sizeof(birdChipListTable) / sizeof(birdChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CBirdChip* birdchip = new CBirdChip;
		birdchip->SetPosition(birdChipListTable[a].pos);
		birdchip->Init(birdChipListTable[a].modelName, g_pd3dDevice);
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
	D3DXMATRIX projMatrix)
{
	for (int a = 0; a < tableSize; a++)
	{
		birdChipList[a]->Render(viewMatrix, projMatrix);
	}
}
