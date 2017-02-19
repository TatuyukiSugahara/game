#pragma once 
#include "Frame\2DImage.h"

class CBossName : public C2DImage
{
public:
	CBossName();
	~CBossName();
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
	void SetRender(bool flag)
	{
		renderflag = flag;
	}
private:
	bool renderflag = false;
};