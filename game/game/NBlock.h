#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SBlockChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�傫��	
};


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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*> nblockChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
	SBlockChipLocInfo* nblockChipLocTable;
	std::unique_ptr<CSoundSource> seBlock;
};
