#include "stdafx.h"
#include "Coin.h"
#include "CoinChip.h"

using namespace std;


//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SCoinChipLocInfo coinChipLocInfoTable[] = {
#include "LocationCoin.h"
};

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
SCoinChipLocInfo coinChipLocInfoTable2[] = {
#include "LocationCoin2.h"
};


CCoin::CCoin()
{

}
CCoin::~CCoin()
{
	for (auto& coinchip : coinChipList){
		delete coinchip;
	}
}
void CCoin::Init()
{
	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
		coinChipLocTable = coinChipLocInfoTable;
		tableSize = sizeof(coinChipLocInfoTable) / sizeof(coinChipLocInfoTable[0]);
		break;
	case Stage2:
		coinChipLocTable = coinChipLocInfoTable2;
		tableSize = sizeof(coinChipLocInfoTable2) / sizeof(coinChipLocInfoTable2[0]);
		break;
	}
	//�z�u��񂩂�}�b�v���\�z
	for (int a = 0; a < tableSize; a++)
	{
		//�}�b�v�`�b�v�𐶐�
		CCoinChip* coinchip = new CCoinChip;
		coinchip->SetPos(coinChipLocTable[a].pos);
		coinchip->Init(coinChipLocTable[a].modelName, g_pd3dDevice);
		coinChipList.push_back(coinchip);
	}

}
void CCoin::Update()
{
	//���[���h�s��̍X�V�B
	static float rot = 0.0f;
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rot += 0.1f);

	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->SetRot(rotation);
		coinChipList[a]->Update();
	}
}
void CCoin::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	for (int a = 0; a < tableSize; a++)
	{
		coinChipList[a]->Render(viewMatrix,projMatrix,isDrawToShadowMap);
	}
}

void CCoin::Release()
{
	auto it = coinChipList.begin();
	while (it != coinChipList.end())
	{
		if ((*it)->GetCoin() == true)
		{
			delete *it;
			it = coinChipList.erase(it);
		}
		else
		{
			it++;
		}
	}
}