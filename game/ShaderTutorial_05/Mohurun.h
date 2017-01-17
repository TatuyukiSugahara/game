#pragma once

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
	int tableSize;
};

