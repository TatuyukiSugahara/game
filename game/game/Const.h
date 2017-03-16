#pragma once

class CConst
{
public:
	static const D3DXVECTOR3 Vec3Zero;							// 0.0f, 0.0f, 0.0f
	static const D3DXVECTOR3 Vec3Right;							// 1.0f, 0.0f, 0.0f	
	static const D3DXVECTOR3 Vec3Left;						//-1.0f, 0.0f, 0.0f
	static const D3DXVECTOR3 Vec3Up;							//0.0f, 1.0f, 0.0f
	static const D3DXVECTOR3 Vec3Down;						//0.0f, -1.0f, 0.0f	
	static const D3DXVECTOR3 Vec3Front;							//0.0f, 0.0f, 1.0f
	static const D3DXVECTOR3 Vec3Back;						//0.0f, 0.0f, -1.0f

	static 	const D3DXVECTOR3 Vec3AxisX;							//1.0f, 0.0f, 0.0f
	static const D3DXVECTOR3 Vec3AxisY;							//0.0f, 1.0f, 0.0f
	static const D3DXVECTOR3 Vec3AxisZ;							//0.0f, 0.0f, 1.0f
	static const D3DXVECTOR3 Vec3One;							//1.0f, 1.0f, 1.0f

	static const D3DXQUATERNION QuaternionIdentity;		//0.0f, 0.0f, 0.0f, 1.0f

	static const float Radian180;							//180“x
	static const float Radian90;							//90“x
	static const float Radian45;							//45“x
	static const float DeltaTime;						//60FPS‚ÌŽžŠÔ
};
