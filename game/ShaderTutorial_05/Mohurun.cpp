#include "stdafx.h"
#include "Mohurun.h"
#include "MohurunChip.h"
#include "Stage.h"


using namespace std;

//マップチップの配置情報のテーブル。
SMohurunChipLocInfo mohurunChipListTable[] = {
#include "LocationMohurun.h"
};

CMohurun::CMohurun()
{
}


CMohurun::~CMohurun()
{
	for (auto& mohurunchip : mohurunChipList){
		delete mohurunchip;
	}
}

//初期化。
void CMohurun::Init()
{
	//配置情報からマップを構築
	tableSize = sizeof(mohurunChipListTable) / sizeof(mohurunChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CMohurunChip* mohurunchip = new CMohurunChip;
		mohurunchip->SetPosition(mohurunChipListTable[a].pos);
		mohurunchip->Init(mohurunChipListTable[a].modelName, g_pd3dDevice);
		mohurunChipList.push_back(mohurunchip);
	}
}
//更新。
void CMohurun::Update()
{
	tableSize = sizeof(mohurunChipListTable) / sizeof(mohurunChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		mohurunChipList[a]->Update();
	}
}
//描画。
void CMohurun::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		mohurunChipList[a]->Render(viewMatrix, projMatrix,isDrawToShadowMap);
	}
}
