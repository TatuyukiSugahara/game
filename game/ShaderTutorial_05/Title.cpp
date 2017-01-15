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
	position = D3DXVECTOR2(465, 260);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/title.png";
	C2DImage::Init();
}

void CTitle::Update()
{
	this->SetupMatrices();
}