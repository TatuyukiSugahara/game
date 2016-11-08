#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Init()
{
	position = D3DXVECTOR2(475, 260);
	angle = 0;
	scale = D3DXVECTOR2(4.8, 3);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/title.png";
	C2DImage::Init();
}

void CTitle::Update()
{
	this->SetupMatrices();
}