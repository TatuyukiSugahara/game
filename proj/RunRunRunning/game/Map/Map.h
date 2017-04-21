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
	//������
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	////�z�u���̃e�[�u���T�C�Y�Q�b�g
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CMapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	SMapChipLocInfo*		mapChipTable;	////�z�u���̃e�[�u��
	int						tableSize;		////�z�u���̃e�[�u���T�C�Y
};
