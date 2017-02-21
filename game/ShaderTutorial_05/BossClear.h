#pragma once 
#include "Frame\2DImage.h"

class CBossClear : public C2DImage
{
public:
	CBossClear();
	~CBossClear();
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
	void SetClear(bool flag)
	{
		Clear = flag;
	}
private:
	bool Clear;
	bool flag = false;		//SEñ¬ÇÁÇ∑ÉtÉâÉOÅB
	CSoundSource* SEGoal;
};