#pragma once 
#include "Frame\2DImage.h"

class CBossLifeChip;

class CBossLife : public C2DImage
{
public:
	CBossLife();
	~CBossLife();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE)override;
	void SetColor(int r, int g, int b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
	std::vector<CBossLifeChip*> bossLifeChipList;	//マップチップのリスト。
	int tableSize;
	D3DXVECTOR2 position[5];
};