#pragma once 
#include "Frame\2DImage.h"

class CBossLifeChip;
class CBossLifeWakuChip;

class CBossLife : public C2DImage
{
public:
	CBossLife();
	~CBossLife();
	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Render(LPD3DXSPRITE)override;
private:
	std::vector<CBossLifeChip*> bossLifeChipList;	//ボスライフチップのリスト。
	std::vector<CBossLifeWakuChip*> bossLifewakuChipList;	//ボスライフチップのリスト。
	int tableSize;
	D3DXVECTOR2 position[5];
	const int BOSSLIFE = 5;
};