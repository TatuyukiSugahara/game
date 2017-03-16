#include "stdafx.h"
#include "Mohurun.h"
#include "MohurunChip.h"
#include "Stage.h"


using namespace std;

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMohurunChipLocInfo mohurunChipListTable[] = {
#include "LocationMohurun.h"
};

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMohurunChipLocInfo mohurunChipListTable2[] = {
#include "LocationMohurun2.h"
};

CMohurun::CMohurun()
{
	mohurunChipLoc = NULL;
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
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		mohurunChipLoc = mohurunChipListTable;
		tableSize = sizeof(mohurunChipListTable) / sizeof(mohurunChipListTable[0]);
		break;
	case CSceneManager::StageNumber::Stage2:
		mohurunChipLoc = mohurunChipListTable2;
		tableSize = sizeof(mohurunChipListTable2) / sizeof(mohurunChipListTable2[0]);
		break;
	}

	//�z�u��񂩂�}�b�v���\�z
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CMohurunChip* mohurunchip = new CMohurunChip;
		mohurunchip->SetPosition(mohurunChipLoc[a].pos);
		mohurunchip->Init(mohurunChipLoc[a].modelName, g_pd3dDevice);
		mohurunChipList.push_back(mohurunchip);
	}
}
//�X�V�B
void CMohurun::Update()
{
	for (auto p : mohurunChipList)
	{
		p->Update();
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

D3DXVECTOR3 CMohurun::GetPos(int i)
{
	return mohurunChipList[i]->GetPos();
}