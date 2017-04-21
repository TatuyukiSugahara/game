#include "stdafx.h"
#include "Const.h"

const D3DXVECTOR3 CConst::Vec3Zero = { 0.0f, 0.0f, 0.0f };							// 0.0f, 0.0f, 0.0f
const D3DXVECTOR3 CConst::Vec3Right = { 1.0f, 0.0f, 0.0f };							// 1.0f, 0.0f, 0.0f	
const D3DXVECTOR3 CConst::Vec3Left = { -1.0f, 0.0f, 0.0f };							//-1.0f, 0.0f, 0.0f
const D3DXVECTOR3 CConst::Vec3Up = { 0.0f, 1.0f, 0.0f };							//0.0f, 1.0f, 0.0f
const D3DXVECTOR3 CConst::Vec3Down = { 0.0f, -1.0f, 0.0f };							//0.0f, -1.0f, 0.0f	
const D3DXVECTOR3 CConst::Vec3Front = { 0.0f, 0.0f, 1.0f };							//0.0f, 0.0f, 1.0f
const D3DXVECTOR3 CConst::Vec3Back = { 0.0f, 0.0f, -1.0f };							//0.0f, 0.0f, -1.0f

const D3DXVECTOR3 CConst::Vec3AxisX = { 1.0f, 0.0f, 0.0f };							//1.0f, 0.0f, 0.0f
const D3DXVECTOR3 CConst::Vec3AxisY = { 0.0f, 1.0f, 0.0f };							//0.0f, 1.0f, 0.0f
const D3DXVECTOR3 CConst::Vec3AxisZ = { 0.0f, 0.0f, 1.0f };							//0.0f, 0.0f, 1.0f
const D3DXVECTOR3 CConst::Vec3One = { 1.0f, 1.0f, 1.0f };							//1.0f, 1.0f, 1.0f

const D3DXQUATERNION CConst::QuaternionIdentity = { 0.0f, 0.0f, 0.0f, 1.0f };		//0.0f, 0.0f, 0.0f, 1.0f

const float CConst::Radian180 = D3DX_PI;											//180“x
const float CConst::Radian90 = D3DX_PI / 2;											//90“x
const float CConst::Radian45 = D3DX_PI / 4;											//45“x
const float CConst::DeltaTime = 1.0f / 60.0f;										//60FPS‚ÌŽžŠÔ