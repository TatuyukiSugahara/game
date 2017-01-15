#pragma once 
#include "Frame\2DImage.h"

class CCoinNomber : public C2DImage
{
public:
	CCoinNomber();
	~CCoinNomber();
	void Init()override;
	void Update()override;
	void Render(LPD3DXSPRITE)override;
	void Render(LPD3DXSPRITE, int num, D3DXVECTOR2 pos);
	void AddNum(int i)
	{
		num++;
	}
	void SetPos(D3DXVECTOR2 pos)
	{
		position = pos;
	}
private:
	const int NUMBER_NUM = 10;
	int num = 0;
};