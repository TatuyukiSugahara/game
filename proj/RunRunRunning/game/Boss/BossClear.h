#pragma once 
#include "Frame\2DImage.h"

class CBossClear : public C2DImage
{
public:
	CBossClear();
	~CBossClear();
	//������
	void Init()override;
	//�X�V
	void Update()override;
	//�`��
	void Render(LPD3DXSPRITE)override;
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
	//�N���A�t���O�Z�b�g
	void SetClear(const bool& flag)
	{
		Clear = flag;
	}
private:
	bool							Clear;				//�N���A�������̃t���O
	bool							flag = false;		//SE�炷�t���O�B
	std::unique_ptr<CSoundSource>	seGoal;				//�N���ASE
};