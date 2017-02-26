#pragma once

//マップチップの配置情報。
struct SBirdChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};

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
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	std::vector<CBirdChip*> GetBird()
	{
		return birdChipList;
	}
private:
	std::vector<CBirdChip*> birdChipList;	//マップチップのリスト。
	SBirdChipLocInfo* birdChipLoc;

	int tableSize;
};

