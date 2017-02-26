#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SBirdChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;		//��]�B
};

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
	SBirdChipLocInfo* birdChipLoc;

	int tableSize;
};

