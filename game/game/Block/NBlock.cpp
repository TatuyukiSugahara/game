#include "stdafx.h"
#include "NBlock.h"
#include "NBlockChip.h"
#include "Map\Stage.h"

using namespace std;

//�u���b�N�`�b�v�̔z�u���̃e�[�u���B
SBlockChipLocInfo nBlockChipLocInfoTable[] = {
#include "Location\LocationBlock.h"
};

CNBlock::CNBlock()
{

}
CNBlock::~CNBlock()
{
	for (auto& blockChip : nblockChipList){
		delete blockChip;
	}
}
void CNBlock::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{

	//�z�u��񂩂�u���b�N���\�z
	tableSize = sizeof(nBlockChipLocInfoTable) / sizeof(nBlockChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//�u���b�N�`�b�v�𐶐�
		CNBlockChip* blockChip = new CNBlockChip;
		blockChip->SetPos(nBlockChipLocInfoTable[a].pos);
		blockChip->SetRot(nBlockChipLocInfoTable[a].rotation);
		blockChip->SetScale(nBlockChipLocInfoTable[a].scale);
		blockChip->Init();
		nblockChipList.push_back(blockChip);
	}

	

}
void CNBlock::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		//�u���b�N�Ɠ��������H
		if (nblockChipList[a]->GetBlock() == g_stage->GetPlayer()->GetcharacterController().getCollisionObj()
			&& g_stage->GetPlayer()->GetcharacterController().IsCeiling() == true)
		{
			seBlock.reset(new CSoundSource);
			seBlock->Init("Asset/Sound/block.wav");
			seBlock->Play(false);
			seBlock->SetVolume(0.25f);
			nblockChipList[a]->SetLost(true);
			nblockChipList[a]->SetParFlag(true);
		}
		nblockChipList[a]->Update();
	}

}
void CNBlock::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		nblockChipList[a]->Render(
			viewMatrix,
			projMatrix,
			isDrawToShadowMap);
	}
	
}