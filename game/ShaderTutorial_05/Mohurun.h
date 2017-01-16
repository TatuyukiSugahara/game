#pragma once

class CMohurunChip;

class CMohurun
{
public:
	CMohurun();
	~CMohurun();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
private:
	std::vector<CMohurunChip*> mohurunChipList;	//マップチップのリスト。
	int tableSize;
};

