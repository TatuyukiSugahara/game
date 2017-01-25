#include "stdafx.h"
#include "TitleStartBG.h"


CTitleStartBG::CTitleStartBG()
{
}


CTitleStartBG::~CTitleStartBG()
{
}

void CTitleStartBG::Init()
{
	position = D3DXVECTOR2(465.0f, 380.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(150, 255, 255, 255);
	texFileName = "Asset/model/title_startBG.png";
	C2DImage::Init();
}

void CTitleStartBG::Update()
{
	
	this->SetupMatrices();
}