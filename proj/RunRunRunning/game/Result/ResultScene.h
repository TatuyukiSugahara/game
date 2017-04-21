#pragma once 
#include "Scene\Scene.h"
#include "ResultDeath.h"
#include "ResultCamera.h"
#include "ResultLight.h"
#include "ResultGoal.h"
#include "Fade.h"
#include "Coin\CoinNomber.h"
#include "Coin\CoinGet.h"

class CResultScene : public CScene
{
public:
	//リザルト画面の選択
	enum class ResultState
	{
		Goal,		//ゴールした場合
		Death,		//死んだ場合
	};
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
	CCoinNomber coinnumber;			//コインナンバー
	CCoinGet	coinGet;			//コインスプライト

};

extern CResultScene* g_resultscene;