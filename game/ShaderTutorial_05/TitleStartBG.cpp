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
	position = D3DXVECTOR2(465.0f, 410.0f);
	angle = 0;
	scale = D3DXVECTOR2(0.6f, 0.8f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/titlestartBG.png";
	C2DImage::Init();
}

void CTitleStartBG::Update()
{
	if (alpha <= 50)
	{
		alp = false;

	}
	else if (alpha >= 254)
	{
		alp = true;

	}
	if (alp == true)
	{
		backColor = D3DCOLOR_ARGB(alpha -= 2, 255, 255, 255);
	}
	else
	{
		backColor = D3DCOLOR_ARGB(alpha += 2, 255, 255, 255);
	}
	this->SetupMatrices();
}