#pragma once 
#include "Frame\2DImage.h"

class CBossLifeChip;
class CBossLifeWakuChip;

class CBossLife : public C2DImage
{
public:
	CBossLife();
	~CBossLife();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE)override;
private:
	std::vector<CBossLifeChip*> bossLifeChipList;	//マップチップのリスト。
	std::vector<CBossLifeWakuChip*> bossLifewakuChipList;	//マップチップのリスト。
	int tableSize;
	D3DXVECTOR2 position[5];
	const int BOSSLIFE = 5;
};