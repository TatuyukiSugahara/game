#pragma once

//鳥チップの配置情報。
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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//鳥のテーブルゲット
	std::vector<CBirdChip*> GetBird()
	{
		return birdChipList;
	}
private:
	std::vector<CBirdChip*>		birdChipList;	//鳥チップのリスト。
	SBirdChipLocInfo*			birdChipLoc;	//配置情報のテーブル
	int							tableSize;		//配置情報のテーブルサイズ
};

