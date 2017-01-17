#include "stdafx.h"
#include "Mohurun.h"
#include "MohurunChip.h"
#include "Stage.h"


using namespace std;

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
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

//�������B
void CMohurun::Init()
{
	//�z�u��񂩂�}�b�v���\�z
	tableSize = sizeof(mohurunChipListTable) / sizeof(mohurunChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CMohurunChip* mohurunchip = new CMohurunChip;
		mohurunchip->SetPosition(mohurunChipListTable[a].pos);
		mohurunchip->Init(mohurunChipListTable[a].modelName, g_pd3dDevice);
		mohurunChipList.push_back(mohurunchip);
	}
}
//�X�V�B
void CMohurun::Update()
{
	tableSize = sizeof(mohurunChipListTable) / sizeof(mohurunChipListTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		mohurunChipList[a]->Update();
	}
}
//�`��B
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
