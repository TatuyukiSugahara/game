#pragma once

//�}�b�v�`�b�v�̔z�u���B
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
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	D3DXVECTOR3 GetPos(int i);
	int GetTableSize()
	{
		return tableSize;
	}
private:
	std::vector<CMohurunChip*> mohurunChipList;	//�}�b�v�`�b�v�̃��X�g�B
	SMohurunChipLocInfo* mohurunChipLoc;
	int tableSize;
};

