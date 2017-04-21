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
	//���U���g��ʂ̑I��
	enum class ResultState
	{
		Goal,		//�S�[�������ꍇ
		Death,		//���񂾏ꍇ
	};
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

	CFade fade;
	CCoinNomber coinnumber;			//�R�C���i���o�[
	CCoinGet	coinGet;			//�R�C���X�v���C�g

};

extern CResultScene* g_resultscene;