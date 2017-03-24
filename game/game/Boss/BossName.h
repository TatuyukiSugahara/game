#pragma once 
#include "Frame\2DImage.h"

class CBossName : public C2DImage
{
public:
	CBossName();
	~CBossName();
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
	//�`�悷�邩�t���O�Z�b�g
	void SetRender(const bool& flag)
	{
		renderFlag = flag;
	}
private:
	bool renderFlag = false;	//�`�悷�邩�̃t���O
};