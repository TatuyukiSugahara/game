#pragma once 
#include "Frame\2DImage.h"

class CBossKatto : public C2DImage
{
public:
	CBossKatto();
	~CBossKatto();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE) override;
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	void SetColor(const int& r, const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
	void SetKatto(const bool& flag)
	{
		KattoFlag = flag;
	}
private:
	bool KattoFlag;
	bool flag = false;			//SE�Ȃ炷�ӂ炮�B
	std::unique_ptr<CSoundSource> SEKatto;
};