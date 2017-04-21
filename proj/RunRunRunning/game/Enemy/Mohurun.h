#pragma once

//���t�����`�b�v�̔z�u���B
struct SMohurunChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;		//��]�B
};

class CMohurunChip;

class CMohurun
{
public:
	CMohurun();
	~CMohurun();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//�e���t�����̃|�W�V�����Q�b�g
	D3DXVECTOR3 GetPos(int i);
	//�z�u���̃e�[�u���̃T�C�Y�Q�b�g
	const int& GetTableSize() const
	{
		return tableSize;
	}
private:
	std::vector<CMohurunChip*>	mohurunChipList;	//���t�����`�b�v�̃��X�g�B
	SMohurunChipLocInfo*		mohurunChipLoc;		//�G�z�u���̃e�[�u���B
	int							tableSize;			//�z�u���̃e�[�u���̃T�C�Y
};

