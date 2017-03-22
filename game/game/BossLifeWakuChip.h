#pragma once 
#include "Frame\2DImage.h"

class CBossLifeWakuChip : public C2DImage
{
public:
	CBossLifeWakuChip();
	~CBossLifeWakuChip();
	//������
	void Init()override;
	//�X�V
	void Update()override;
	//���W�Z�b�g
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	//�J���[�Z�b�g
	void SetColor(const int& r, const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
};