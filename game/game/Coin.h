#pragma once

//マップチップの配置情報。
struct SCoinChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
};

class CCoinChip;

/*!
* @brief	マップクラス。
*/
class CCoin {
public:

	CCoin();
	~CCoin();
	void Init();
	void Update();
	void Release();
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
	std::vector<CCoinChip*> coinChipList;	//マップチップのリスト。
	int tableSize;
	SCoinChipLocInfo* coinChipLocTable;
	D3DXQUATERNION						rotation;
};
