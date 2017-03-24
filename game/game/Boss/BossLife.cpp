#include "stdafx.h"
#include "Map\Stage.h"
#include "BossLife.h"
#include "BossLifeChip.h"
#include "BossLifeWakuChip.h"


CBossLife::CBossLife()
{
	position[0] = D3DXVECTOR2(740.0, 480.0f);
	position[1] = D3DXVECTOR2(680.0, 480.0f);
	position[2] = D3DXVECTOR2(620.0, 480.0f);
	position[3] = D3DXVECTOR2(560.0, 480.0f);
	position[4] = D3DXVECTOR2(500.0, 480.0f);
}


CBossLife::~CBossLife()
{
	for (auto& lifechip : bossLifeChipList){
		delete lifechip;
	}
	for (auto& lifewakuchip : bossLifewakuChipList){
		delete lifewakuchip;
	}
}

void CBossLife::Init()
{
	
	for (int a = 0; a < BOSSLIFE; a++)
	{
		CBossLifeWakuChip* lifewakuChip = new CBossLifeWakuChip;
		lifewakuChip->Init();
		lifewakuChip->SetPos(position[a]);
		bossLifewakuChipList.push_back(lifewakuChip);
	}
	for (int a = 0; a < g_stage->GetBoss()->GetLife(); a++)
	{
		CBossLifeChip* lifeChip = new CBossLifeChip;
		lifeChip->Init();
		lifeChip->SetPos(position[a]);
		bossLifeChipList.push_back(lifeChip);
	}
}

void CBossLife::Update()
{
	
	for (int a = 0; a < BOSSLIFE; a++)
	{
		bossLifewakuChipList[a]->Update();
	}
	for (int a = 0; a < g_stage->GetBoss()->GetLife(); a++)
	{
		bossLifeChipList[a]->Update();
	}
}

void CBossLife::Render(LPD3DXSPRITE pSprite)
{
	if (g_stage->GetBoss()->Start() == true && g_stage->GetBoss()->GetLife() > 0)
	{
		
		for (int a = 0; a < BOSSLIFE; a++)
		{
			bossLifewakuChipList[a]->Render(pSprite);
		}
		for (int a = 0; a < g_stage->GetBoss()->GetLife(); a++)
		{
			bossLifeChipList[a]->Render(pSprite);
		}
	}
}