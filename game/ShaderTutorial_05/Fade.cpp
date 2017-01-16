#include "stdafx.h"
#include "Fade.h"


CFade::CFade()
{
}


CFade::~CFade()
{
}

void CFade::Init()
{
	position = D3DXVECTOR2(465, 260);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	texFileName = "Asset/model/fade.png";
	C2DImage::Init();
}

void CFade::Update()
{
	this->SetupMatrices();
}
