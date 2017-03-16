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
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	void SetColor(const int& r, const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
	void SetClear(const bool& flag)
	{
		Clear = flag;
	}
private:
	bool Clear;
	bool flag = false;		//SEñ¬ÇÁÇ∑ÉtÉâÉOÅB
	std::unique_ptr<CSoundSource> SEGoal;
};