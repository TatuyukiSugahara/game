#pragma once

//モフルンチップの配置情報。
struct SMohurunChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};

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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//各モフルンのポジションゲット
	D3DXVECTOR3 GetPos(int i);
	//配置情報のテーブルのサイズゲット
	const int& GetTableSize() const
	{
		return tableSize;
	}
private:
	std::vector<CMohurunChip*>	mohurunChipList;	//モフルンチップのリスト。
	SMohurunChipLocInfo*		mohurunChipLoc;		//敵配置情報のテーブル。
	int							tableSize;			//配置情報のテーブルのサイズ
};

