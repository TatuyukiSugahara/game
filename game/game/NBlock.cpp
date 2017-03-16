#include "stdafx.h"
#include "NBlock.h"
#include "NBlockChip.h"
#include "Stage.h"

using namespace std;

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SBlockChipLocInfo nblockChipLocInfoTable[] = {
#include "LocationBlock.h"
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

	//�z�u��񂩂�}�b�v���\�z
	tableSize = sizeof(nblockChipLocInfoTable) / sizeof(nblockChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CNBlockChip* blockChip = new CNBlockChip;
		blockChip->SetPos(nblockChipLocInfoTable[a].pos);
		blockChip->SetRot(nblockChipLocInfoTable[a].rotation);
		blockChip->SetScale(nblockChipLocInfoTable[a].scale);
		blockChip->Init();
		nblockChipList.push_back(blockChip);
	}

	

}
void CNBlock::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		//�u���b�N�Ɠ��������H
		if (nblockChipList[a]->Get2DBlock() == g_stage->GetPlayer()->GetcharacterController().getCollisionObj()
			&& g_stage->GetPlayer()->GetcharacterController().IsCeiling() == true)
		{
			SEBlock.reset(new CSoundSource);
			SEBlock->Init("Asset/Sound/block.wav");
			SEBlock->Play(false);
			SEBlock->SetVolume(0.25f);
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