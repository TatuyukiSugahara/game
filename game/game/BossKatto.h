#pragma once 
#include "Frame\2DImage.h"

class CBossKatto : public C2DImage
{
public:
	CBossKatto();
	~CBossKatto();
	//������
	void Init()override;
	//�X�V
	void Update()override;
	//�`��
	void Render(LPD3DXSPRITE pSprite)override;
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
	//�J�b�g�C���o�����t���O
	void SetKatto(const bool& flag)
	{
		kattoFlag = flag;
	}
private:
	bool							kattoFlag;			//�J�b�g�C���o�����t���O
	bool							flag = false;		//SE�Ȃ炷�ӂ炮�B
	std::unique_ptr<CSoundSource>	seKatto;			//�J�b�g�C��SE
};