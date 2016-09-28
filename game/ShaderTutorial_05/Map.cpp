#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

using namespace std;


//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SMapChipLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
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
	//�z�u��񂩂�}�b�v���\�z
	tableSize = sizeof(mapChipLocInfoTable) / sizeof(mapChipLocInfoTable[0]);
	for (int a=0; a < tableSize;a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CMapChip* mapChip = new CMapChip;
		mapChip->SetPos(mapChipLocInfoTable[a].pos);
		mapChip->SetRot(mapChipLocInfoTable[a].rotation);
		mapChip->Init(mapChipLocInfoTable->modelName, pd3dDevice);
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
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	for (int a = 0; a < tableSize; a++)
	{
		mapChipList[a]->Render(
			pd3dDevice,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight
			);
	}
}