#include "stdafx.h"
#include "Coin.h"
#include "CoinChip.h"

using namespace std;


//マップチップの配置情報のテーブル。
SCoinChipLocInfo coinChipLocInfoTable[] = {
#include "LocationCoin.h"
};

//マップチップの配置情報のテーブル。
SCoinChipLocInfo coinChipLocInfoTable2[] = {
#include "LocationCoin2.h"
};


CCoin::CCoin()
{

}
CCoin::~CCoin()
{
	for (auto& coinchip : coinChipList){
		delete coinchip;
	}
}
void CCoin::Init()
{
	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
		coinChipLocTable = coinChipLocInfoTable;
		tableSize = sizeof(coinChipLocInfoTable) / sizeof(coinChipLocInfoTable[0]);
		break;
	case Stage2:
		coinChipLocTable = coinChipLocInfoTable2;
		tableSize = sizeof(coinChipLocInfoTable2) / sizeof(coinChipLocInfoTable2[0]);
		break;
	}
	//配置情報からマップを構築
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CCoinChip* coinchip = new CCoinChip;
		coinchip->SetPos(coinChipLocTable[a].pos);
		coinchip->Init(coinChipLocTable[a].modelName, g_pd3dDevice);
		coinChipList.push_back(coinchip);
	}

}
void CCoin::Update()
{
	//ワールド行列の更新。
	static float rot = 0.0f;
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rot += 0.1f);

	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->SetRot(rotation);
		coinChipList[a]->Update();
	}
}
void CCoin::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->Render(viewMatrix,projMatrix,isDrawToShadowMap);
	}
}

void CCoin::Release()
{
	auto it = coinChipList.begin();
	while (it != coinChipList.end())
	{
		if ((*it)->GetCoin() == true)
		{
			delete *it;
			it = coinChipList.erase(it);
		}
		else
		{
			it++;
		}
	}
}