#pragma once 
#include "Frame\2DImage.h"

class CBossLifeWakuChip : public C2DImage
{
public:
	CBossLifeWakuChip();
	~CBossLifeWakuChip();
	void Init()override;
	void Update()override;
	void SetPos(D3DXVECTOR2 pos)
	{
		position = pos;
	}
	void SetColor(int r, int g, int b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
};