#pragma once 
#include "Frame\2DImage.h"

class CResultDeath : public C2DImage
{
public:
	CResultDeath();
	~CResultDeath();
	void Init()override;
	void Update()override;

private:
	CSoundSource* SEDeath;
};