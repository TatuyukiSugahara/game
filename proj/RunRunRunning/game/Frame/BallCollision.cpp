#include "stdafx.h"
#include "BallCollision.h"


bool BallCollision(const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, float r1, float r2)
{

	float length = (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) + (p2.z - p1.z)*(p2.z - p1.z);
	if (length <= (r1 + r2)*(r1 + r2))
	{
		return true;
	}
	return false;
}