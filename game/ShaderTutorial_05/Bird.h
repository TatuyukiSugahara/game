#pragma once

class CBirdChip;

class CBird
{
public:
	CBird();
	~CBird();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
private:
	std::vector<CBirdChip*> birdChipList;	//マップチップのリスト。
	int tableSize;
};

