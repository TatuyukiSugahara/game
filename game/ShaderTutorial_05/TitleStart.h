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
	bool alp = true;			//TRUE = ���Z, FALSE = ���Z	
	int alpha = 200;
};