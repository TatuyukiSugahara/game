#include "stdafx.h"
#include "ResultGoal.h"


CResultGoal::CResultGoal()
{
}


CResultGoal::~CResultGoal()
{
	if (SEGoal)
	{
		delete SEGoal;
	}
}

void CResultGoal::Init()
{
	position = D3DXVECTOR2(475, 260);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/goal.png";
	C2DImage::Init();

	SEGoal = new CSoundSource;
	SEGoal->Init("Asset/Sound/goal.wav");
	SEGoal->Play(false);
}

void CResultGoal::Update()
{
	this->SetupMatrices();
}