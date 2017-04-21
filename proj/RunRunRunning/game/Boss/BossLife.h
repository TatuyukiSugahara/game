#pragma once 
#include "Frame\2DImage.h"

class CBossLifeChip;
class CBossLifeWakuChip;

class CBossLife : public C2DImage
{
public:
	CBossLife();
	~CBossLife();
	//������
	void Init()override;
	//�X�V
	void Update()override;
	//�`��
	void Render(LPD3DXSPRITE)override;
private:
	std::vector<CBossLifeChip*> bossLifeChipList;	//�{�X���C�t�`�b�v�̃��X�g�B
	std::vector<CBossLifeWakuChip*> bossLifewakuChipList;	//�{�X���C�t�`�b�v�̃��X�g�B
	int tableSize;
	D3DXVECTOR2 position[5];
	const int BOSSLIFE = 5;
};