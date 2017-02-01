#include "stdafx.h"
#include "TitleStart.h"


CTitleStart::CTitleStart()
{
}


CTitleStart::~CTitleStart()
{
}

void CTitleStart::Init()
{
	position = D3DXVECTOR2(465.0f, 380.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/title_start.png";
	C2DImage::Init();
}

void CTitleStart::Update()
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