#pragma once 
#include "Scene\Scene.h"
#include "ResultDeath.h"
#include "ResultCamera.h"
#include "ResultLight.h"
#include "ResultGoal.h"
#include "Fade.h"

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
	HRESULT CreateSprite();	//スプライト生成関数
	void SetState(ResultState sta)
	{
		state = sta;
	}

private:
	LPD3DXSPRITE m_pSprite;			//スプライト
	CResultDeath resultDeat;		//デス画面
	CResultCamera resultcamera;		//かめら
	CResultLight resultlight;		//ライト
	CResultGoal resultGoal;			//ゴール
	ResultState state;

	CFade fade;

};

extern CResultScene* g_resultscene;