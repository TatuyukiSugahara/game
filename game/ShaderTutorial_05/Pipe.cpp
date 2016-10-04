#include "stdafx.h"
#include "Pipe.h"
#include "PipeChip.h"

using namespace std;


//マップチップの配置情報のテーブル。
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
	//配置情報からマップを構築
	tableSize = sizeof(pipeChipLocInfoTable) / sizeof(pipeChipLocInfoTable[0]);
	for (int a = 0; a < tableSize; a++)
	{
		//マップチップを生成
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