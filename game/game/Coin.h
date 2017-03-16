#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SCoinChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
};

class CCoinChip;

/*!
* @brief	�}�b�v�N���X�B
*/
class CCoin {
public:

	CCoin();
	~CCoin();
	void Init();
	void Update();
	void Release();
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
	std::vector<CCoinChip*> coinChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
	SCoinChipLocInfo* coinChipLocTable;
	D3DXQUATERNION						rotation;
};
