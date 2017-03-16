#pragma once 
#include "Frame\2DImage.h"

class CFade : public C2DImage
{
public:
	CFade();
	~CFade();
	void Init()override;
	void Update()override;
	
	void AddScale(D3DXVECTOR2 scale)
	{
			this->scale += scale;
	}
	D3DXVECTOR2 GetScale()
	{
		return scale;
	}
	void AddAlpha(int i)
	{
		if (alpha <= 250)
		{
			alpha += i;
			backColor = D3DCOLOR_ARGB(alpha, 255, 255, 255);
		}
	}
	const float GetNext()
	{
		return NEXT;
	}
	float GetTimer()
	{
		return Timer;
	}
	void SetFade(bool flag)
	{
		Fade = flag;
	}
private:
	int alpha = 0;

	float Timer = 0.0f;
	const float NEXT = 5.0f;
	bool Fade = false;
};