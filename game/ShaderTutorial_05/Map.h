#pragma once

class CMapChip;

/*!
* @brief	マップクラス。
*/
class CMap {
public:

	CMap();
	~CMap();
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CMapChip*> mapChipList;	//マップチップのリスト。
	int tableSize;
};
