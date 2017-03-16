#pragma once 
#include "Frame\2DImage.h"

class CBossLifeChip : public C2DImage
{
public:
	CBossLifeChip();
	~CBossLifeChip();
	void Init()override;
	void Update()override;
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	void SetColor(const int& r, const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
};