#pragma once

//�u���b�N�`�b�v�̔z�u���B
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
	//�R���X�g���N�^
	CNBlock();
	//�f�X�g���N�^
	~CNBlock();
	//������
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//�z�u���̃e�[�u���T�C�Y�Q�b�g
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CNBlockChip*>		nblockChipList;		//�u���b�N�`�b�v�̃��X�g�B
	int								tableSize;			//�z�u���̃e�[�u���̃T�C�Y
	SBlockChipLocInfo*				nBlockChipLocTable;	//�z�u���̃e�[�u��
	std::unique_ptr<CSoundSource>	seBlock;			//�u���b�N������SE
};
