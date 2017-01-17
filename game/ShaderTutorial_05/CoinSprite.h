#pragma once 
#include "Frame\2DImage.h"

class CCoinSprite : public C2DImage
{
public:
	CCoinSprite();
	~CCoinSprite();
	void Init()override;
	void Update()override;
	void SetPos(D3DXVECTOR2 pos)
	{
		position = pos;
	}
private:
};