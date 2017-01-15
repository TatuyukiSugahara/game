#pragma once 
#include "Scene\Scene.h"
#include "ResultDeath.h"
#include "ResultCamera.h"
#include "ResultLight.h"
#include "ResultGoal.h"

enum ResultState
{
	Goal,
	Death,
};

class CResultScene : public CScene
{
public:
	CResultScene(){}
	~CResultScene(){}
	void Init();
	void Update();
	void Render();
	HRESULT CreateSprite();	//�X�v���C�g�����֐�
	void SetState(ResultState sta)
	{
		state = sta;
	}

private:
	LPD3DXSPRITE m_pSprite;			//�X�v���C�g
	CResultDeath resultDeat;		//�f�X���
	CResultCamera resultcamera;		//���߂�
	CResultLight resultlight;		//���C�g
	CResultGoal resultGoal;			//�S�[��
	ResultState state;
};

extern CResultScene* g_resultscene;