#pragma once

//ブロックチップの配置情報。
struct SBlockChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//大きさ	
};


class CNBlockChip;

/*!
* @brief	見えるブロッククラス。
*/
class CNBlock {
public:
	//コンストラクタ
	CNBlock();
	//デストラクタ
	~CNBlock();
	//初期化
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//配置情報のテーブルサイズゲット
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*>		nblockChipList;		//ブロックチップのリスト。
	int								tableSize;			//配置情報のテーブルのサイズ
	SBlockChipLocInfo*				nBlockChipLocTable;	//配置情報のテーブル
	std::unique_ptr<CSoundSource>	seBlock;			//ブロックが壊れるSE
};
