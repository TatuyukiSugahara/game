#pragma once

class CBirdChip;

class CBird
{
public:
	CBird();
	~CBird();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	std::vector<CBirdChip*> GetBird()
	{
		return birdChipList;
	}
private:
	std::vector<CBirdChip*> birdChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
};

