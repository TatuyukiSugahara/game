#pragma once

//マップチップの配置情報。
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

	CNBlock();
	~CNBlock();
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*> nblockChipList;	//マップチップのリスト。
	int tableSize;
	SBlockChipLocInfo* nblockChipLocTable;
	std::unique_ptr<CSoundSource> seBlock;
};
