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
	void Render(const LPD3DXSPRITE, const int num, const D3DXVECTOR2 pos);
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	void Set1keta(const D3DXVECTOR2& keta)
	{
		keta1 = keta;
	}
	void Set2keta(const D3DXVECTOR2& keta)
	{
		keta2 = keta;
	}
	void Set3keta(const D3DXVECTOR2& keta)
	{
		keta3 = keta;
	}
	void SetColor(const int& r,const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
	const int NUMBER_NUM = 10;
	D3DXVECTOR2 keta1;
	D3DXVECTOR2 keta2;
	D3DXVECTOR2 keta3;
};