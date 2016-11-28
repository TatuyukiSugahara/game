#pragma once

class CNBlockChip;

/*!
* @brief	������u���b�N�N���X�B
*/
class CNBlock {
public:

	CNBlock();
	~CNBlock();
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	//�`��B
	void Render();
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*> nblockChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
};
