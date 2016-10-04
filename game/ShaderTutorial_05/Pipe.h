#pragma once

class CPipeChip;

/*!
* @brief	マップクラス。
*/
class CPipe {
public:

	CPipe();
	~CPipe();
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	//描画。
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CPipeChip*> pipeChipList;	//マップチップのリスト。
	int tableSize;
};
