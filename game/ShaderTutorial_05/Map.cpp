#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

using namespace std;


//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMapChipLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
};

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMapChipLocInfo mapChipLocInfoTable2[] = {
#include "locationInfo2.h"
};

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMapChipLocInfo mapChipLocInfoTableBoss[] = {
#include "LocationInfoBos.h"
};

CMap::CMap()
{

}
CMap::~CMap()
{
	for (auto& mapchip : mapChipList){
		delete mapchip;
	}
}
void CMap::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{

	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
		mapChipTable = mapChipLocInfoTable;
		tableSize = sizeof(mapChipLocInfoTable) / sizeof(mapChipLocInfoTable[0]);
		break;
	case Stage2:
		mapChipTable = mapChipLocInfoTable2;
		tableSize = sizeof(mapChipLocInfoTable2) / sizeof(mapChipLocInfoTable2[0]);
		break;
	case StageBoss:
		mapChipTable = mapChipLocInfoTableBoss;
		tableSize = sizeof(mapChipLocInfoTableBoss) / sizeof(mapChipLocInfoTableBoss[0]);
		break;
	}

	//�z�u��񂩂�}�b�v���\�z
	for (int a=0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CMapChip* mapChip = new CMapChip;
		mapChip->SetPos(mapChipTable[a].pos);
		mapChip->SetRot(mapChipTable[a].rotation);
		mapChip->Init(mapChipTable[a].modelName, pd3dDevice);
		mapChipList.push_back(mapChip);
	}
	
}
void CMap::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		mapChipList[a]->Update();
	}
}
void CMap::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	for (int a = 0; a < tableSize; a++)
	{
		mapChipList[a]->Render(
			viewMatrix,
			projMatrix);
	}
}