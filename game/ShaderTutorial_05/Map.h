#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SMapChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;		//��]�B
};

class CMapChip;

/*!
* @brief	�}�b�v�N���X�B
*/
class CMap {
public:

	CMap();
	~CMap();
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CMapChip*> mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	SMapChipLocInfo* mapChipTable;
	int tableSize;
};
