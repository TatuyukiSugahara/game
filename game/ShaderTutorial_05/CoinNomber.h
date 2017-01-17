#pragma once 
#include "Frame\2DImage.h"

class CCoinNomber : public C2DImage
{
public:
	CCoinNomber();
	~CCoinNomber();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE)override;
	void Render(LPD3DXSPRITE, int num, D3DXVECTOR2 pos);
	void SetPos(D3DXVECTOR2 pos)
	{
		position = pos;
	}
	void Set1keta(D3DXVECTOR2 keta)
	{
		keta1 = keta;
	}
	void Set2keta(D3DXVECTOR2 keta)
	{
		keta2 = keta;
	}
	void SetColor(int r,int g, int b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
	const int NUMBER_NUM = 10;
	D3DXVECTOR2 keta1;
	D3DXVECTOR2 keta2;
};