#pragma once

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
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CCoinChip*> coinChipList;	//マップチップのリスト。
	int tableSize;
};
