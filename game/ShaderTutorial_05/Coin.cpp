#include "stdafx.h"
#include "Coin.h"
#include "CoinChip.h"

using namespace std;


//マップチップの配置情報のテーブル。
SCoinChipLocInfo coinChipLocInfoTable[] = {
#include "LocationCoin.h"
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
	//配置情報からマップを構築
	tableSize = sizeof(coinChipLocInfoTable) / sizeof(coinChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
		CCoinChip* coinchip = new CCoinChip;
		coinchip->SetPos(coinChipLocInfoTable[a].pos);
		coinchip->Init(coinChipLocInfoTable[a].modelName, g_pd3dDevice);
		coinChipList.push_back(coinchip);
	}

}
void CCoin::Update()
{
	tableSize = sizeof(coinChipLocInfoTable) / sizeof(coinChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->Update();
	}
	//Release();
}
void CCoin::Render()
{
	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->Render();
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