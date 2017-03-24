#pragma once

//コインチップの配置情報。
struct SCoinChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
};

class CCoinChip;

/*!
* @brief	コインクラス。
*/
class CCoin {
public:

	CCoin();
	~CCoin();
	//初期化
	void Init();
	//更新
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//解放
	void Release();
	//配置情報のテーブルサイズゲット
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CCoinChip*> coinChipList;		//コインチップのリスト。
	int						tableSize;			//配置情報のテーブルサイズ
	SCoinChipLocInfo*		coinChipLocTable;	//配置情報のテーブル
	D3DXQUATERNION			rotation;			//回転
};
