#pragma once 
#include "Frame\2DImage.h"

class CBossKatto : public C2DImage
{
public:
	CBossKatto();
	~CBossKatto();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE)override;
	void SetPos(D3DXVECTOR2 pos)
	{
		position = pos;
	}
	void SetColor(int r, int g, int b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
	void SetKatto(bool flag)
	{
		KattoFlag = flag;
	}
private:
	bool KattoFlag;
};