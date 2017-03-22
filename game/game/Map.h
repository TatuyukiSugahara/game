#pragma once

//マップチップの配置情報。
struct SMapChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};

class CMapChip;

/*!
* @brief	マップクラス。
*/
class CMap {
public:

	CMap();
	~CMap();
	//初期化
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	////配置情報のテーブルサイズゲット
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CMapChip*>	mapChipList;	//マップチップのリスト。
	SMapChipLocInfo*		mapChipTable;	////配置情報のテーブル
	int						tableSize;		////配置情報のテーブルサイズ
};
