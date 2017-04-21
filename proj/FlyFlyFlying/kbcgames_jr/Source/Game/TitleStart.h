#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"



class CTitleStart
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Scale();
private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;

	BYTE diks[256];
	
	float scale;
	const float MAX = 250.0f;
	const float MIN = 200.0f;
};