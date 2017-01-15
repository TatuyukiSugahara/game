#include "stdafx.h"
#include "Bird.h"
#include "BirdChip.h"
#include "Stage.h"

using namespace std;

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
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

//�������B
void CBird::Init()
{
	//�z�u��񂩂�}�b�v���\�z
	tableSize = sizeof(birdChipListTable) / sizeof(birdChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CBirdChip* birdchip = new CBirdChip;
		birdchip->SetPosition(birdChipListTable[a].pos);
		birdchip->Init(birdChipListTable[a].modelName, g_pd3dDevice);
		birdChipList.push_back(birdchip);
	}
}
//�X�V�B
void CBird::Update()
{

	tableSize = sizeof(birdChipListTable) / sizeof(birdChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		birdChipList[a]->Update();
	}

	
}
//�`��B
void CBird::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	for (int a = 0; a < tableSize; a++)
	{
		birdChipList[a]->Render(viewMatrix, projMatrix);
	}
}
