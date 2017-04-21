#pragma once

//���`�b�v�̔z�u���B
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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//���̃e�[�u���Q�b�g
	std::vector<CBirdChip*> GetBird()
	{
		return birdChipList;
	}
private:
	std::vector<CBirdChip*>		birdChipList;	//���`�b�v�̃��X�g�B
	SBirdChipLocInfo*			birdChipLoc;	//�z�u���̃e�[�u��
	int							tableSize;		//�z�u���̃e�[�u���T�C�Y
};

