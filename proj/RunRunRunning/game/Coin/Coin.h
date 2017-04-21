#pragma once

//�R�C���`�b�v�̔z�u���B
struct SCoinChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
};

class CCoinChip;

/*!
* @brief	�R�C���N���X�B
*/
class CCoin {
public:

	CCoin();
	~CCoin();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//���
	void Release();
	//�z�u���̃e�[�u���T�C�Y�Q�b�g
	const int& GetSize() const
	{
		return tableSize;
	}
private:
	std::vector<CCoinChip*> coinChipList;		//�R�C���`�b�v�̃��X�g�B
	int						tableSize;			//�z�u���̃e�[�u���T�C�Y
	SCoinChipLocInfo*		coinChipLocTable;	//�z�u���̃e�[�u��
	D3DXQUATERNION			rotation;			//��]
};
