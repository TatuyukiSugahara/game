#include "stdafx.h"
#include "Stage.h"
#include "BossLife.h"
#include "BossLifeChip.h"


CBossLife::CBossLife()
{
	position[0] = D3DXVECTOR2(910.0, 30.0f);
	position[1] = D3DXVECTOR2(850.0, 30.0f);
	position[2] = D3DXVECTOR2(790.0, 30.0f);
	position[3] = D3DXVECTOR2(730.0, 30.0f);
	position[4] = D3DXVECTOR2(670.0, 30.0f);
}


CBossLife::~CBossLife()
{
	for (auto& lifechip : bossLifeChipList){
		delete lifechip;
	}
}

void CBossLife::Init()
{
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
	for (int a = 0; a < g_stage->GetBoss()->GetLife(); a++)
	{
		bossLifeChipList[a]->Update();
	}
}

void CBossLife::Render(LPD3DXSPRITE pSprite)
{
	if (g_stage->GetBoss()->Start() == true)
	{
		for (int a = 0; a < g_stage->GetBoss()->GetLife(); a++)
		{
			bossLifeChipList[a]->Render(pSprite);
		}
	}
}