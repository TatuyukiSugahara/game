#include "stdafx.h"
#include "CoinNomber.h"


CCoinNomber::CCoinNomber()
{

}


CCoinNomber::~CCoinNomber()
{
}

void CCoinNomber::Init()
{
	position = D3DXVECTOR2(30.0f, 30.0f);
	keta1 = D3DXVECTOR2(180.0f, 30.0f);
	keta2 = D3DXVECTOR2(150.0f, 30.0f);
	keta3 = D3DXVECTOR2(120.0f, 30.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/Number.png";
	C2DImage::Init();
}

void CCoinNomber::Update()
{
	
}

void CCoinNomber::Render(LPD3DXSPRITE pSprite)
{
	Render(pSprite, g_scenemanager->GetNum() % 10, keta1);
	Render(pSprite, (g_scenemanager->GetNum() % 100) / 10, keta2);
	Render(pSprite, g_scenemanager->GetNum() / 100, keta3);
}

void CCoinNomber::Render(LPD3DXSPRITE pSprite, int num, D3DXVECTOR2 pos)
{

	short width = imgInfo.Width / NUMBER_NUM;
	rect = { num*width,	//左座標
		0,						//上座標
		(num + 1) * width,		//右座標
		imgInfo.Height };	//下座標
	texCenter = D3DXVECTOR2(float(width - width / 2),
		float(rect.bottom - rect.bottom / 2));
	position = pos;
	this->SetupMatrices();
	C2DImage::Render(pSprite);
}