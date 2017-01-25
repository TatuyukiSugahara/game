#pragma once 
#include "Frame\2DImage.h"

class CTitleStart : public C2DImage
{
public:
	CTitleStart();
	~CTitleStart();
	void Init()override;
	void Update()override;

private:
	const float MAX_SCALE = 1.2f;
	const float MIN_SCALE = 0.8f;
	bool sca = true;			//TRUE = ‰ÁŽZ , FALSE = Œ¸ŽZ
};