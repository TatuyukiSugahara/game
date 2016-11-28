#pragma once

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
	void Render();
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*> nblockChipList;	//マップチップのリスト。
	int tableSize;
};
