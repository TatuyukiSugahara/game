#pragma once 
#include "Frame\2DImage.h"

class CResultGoal : public C2DImage
{
public:
	CResultGoal();
	~CResultGoal();
	void Init()override;
	void Update()override;

private:

};