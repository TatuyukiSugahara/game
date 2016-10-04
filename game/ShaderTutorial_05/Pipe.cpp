#include "stdafx.h"
#include "Pipe.h"
#include "PipeChip.h"

using namespace std;


//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SPipeChipLocInfo pipeChipLocInfoTable[] = {
#include "locationPipe.h"
};

CPipe::CPipe()
{

}
CPipe::~CPipe()
{
	for (auto& pipechip : pipeChipList){
		delete pipechip;
	}
}
void CPipe::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//�z�u��񂩂�}�b�v���\�z
	tableSize = sizeof(pipeChipLocInfoTable) / sizeof(pipeChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CPipeChip* pipeChip = new CPipeChip;
		pipeChip->SetPos(pipeChipLocInfoTable[a].pos);
		pipeChip->SetRot(pipeChipLocInfoTable[a].rotation);
		pipeChip->SetScale(pipeChipLocInfoTable[a].scale);
		pipeChip->Init(pipeChipLocInfoTable[a].modelName, pd3dDevice);
		pipeChipList.push_back(pipeChip);
	}

}
void CPipe::Update()
{
	for (int a = 0; a < tableSize; a++)
	{
		pipeChipList[a]->Update();
	}
}
void CPipe::Render(
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
		pipeChipList[a]->Render(
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