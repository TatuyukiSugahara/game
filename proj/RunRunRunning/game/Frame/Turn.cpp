#include "stdafx.h"
#include "Turn.h"

namespace
{
	static const float	cTurnSpeed = D3DXToRadian(10.0f);	//�^�[���X�s�[�h
}

CTurn::~CTurn()
{
}

void CTurn::Init()
{
	
	currentAngleY = 0.0f;
	targetAngleY = 0.0f;
	turnSpeed = 0.0f;
	cTurnSpeed = 0.1f;
}

//��]����
float CTurn::Update(bool isTurn, float targetAngleY)
{
	

	if (isTurn) {
		float angleDiff = targetAngleY - currentAngleY;						//�ړI�p�x�܂łǂꂾ���񂹂������̂����v�Z����B
		float angleDiffAbs = fabsf(angleDiff);								//�񂷊p�x�̐�Βl���v�Z�B
		if (angleDiffAbs > 0.0001f) {										//�񂷊p�x�̑傫�������ɏ������ꍇ�͉񂳂Ȃ��B
			float turnDir = angleDiff / angleDiffAbs;						//��]������������v�Z����B
			if (angleDiffAbs > CConst::Radian180) {							//��]������p�x��180�x���z���Ă��邩�𔻒肷��B
				//180�x���z�����]�̂��߉����B
				currentAngleY += 2.0f * CConst::Radian180 *  turnDir;		//���݂̊p�x��-90�x�Ȃ�270�x�A180�x�Ȃ�-180�x�ɂ���B
				turnDir *= -1.0f;											//�񂷕����𔽓]�B
			}
			turnSpeed = cTurnSpeed * turnDir;
		}
	}
	currentAngleY += turnSpeed;
	if (fabsf(targetAngleY - currentAngleY) < fabsf(turnSpeed) + 0.01f) {
		//�^�[���I���B
		turnSpeed = 0.0f;
		currentAngleY = targetAngleY;
	}
	return currentAngleY;
}
