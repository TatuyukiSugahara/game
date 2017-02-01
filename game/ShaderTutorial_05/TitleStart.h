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
	bool alp = true;			//TRUE = Œ¸ŽZ, FALSE = ‰ÁŽZ	
	int alpha = 200;
};