#pragma once 
#include "Frame\2DImage.h"

class CTitleStartBG : public C2DImage
{
public:
	CTitleStartBG();
	~CTitleStartBG();
	void Init()override;
	void Update()override;

private:
};