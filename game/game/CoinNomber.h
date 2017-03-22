#pragma once 
#include "Frame\2DImage.h"

class CCoinNomber : public C2DImage
{
public:
	CCoinNomber();
	~CCoinNomber();
	//������
	void Init()override;
	//�X�V
	void Update()override;
	//�`��
	void Render(LPD3DXSPRITE)override;
	//�����Ƃɕ`�悷�邽��
	void Render(const LPD3DXSPRITE, const int num, const D3DXVECTOR2 pos);
	//���W�Z�b�g
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	//1���ڂ̍��W�Z�b�g
	void Set1keta(const D3DXVECTOR2& keta)
	{
		keta1 = keta;
	}
	//2���ʂ̍��W�Z�b�g
	void Set2keta(const D3DXVECTOR2& keta)
	{
		keta2 = keta;
	}
	//3���ڂ̍��W�Z�b�g
	void Set3keta(const D3DXVECTOR2& keta)
	{
		keta3 = keta;
	}
	//�J���[�Z�b�g
	void SetColor(const int& r,const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
	const int	NUMBER_NUM = 10;	//0����9�̂���10
	D3DXVECTOR2 keta1;				//1����
	D3DXVECTOR2 keta2;				//2����
	D3DXVECTOR2 keta3;				//3����
};