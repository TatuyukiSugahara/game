#pragma once

class CTurn
{
public:
	CTurn()
	{
	};
	~CTurn();
	//��]�����̏�����
	void CTurn::Init();		
	//��]�����̍X�V
	float CTurn::Update(bool isTurn, float currentAngleY);
private:
	float	currentAngleY;		//���݂̕���
	float	targetAngleY;		//������������
	float	turnSpeed;			//��]���x
	float   cTurnSpeed;			//�^�[���X�s�[�h
	bool	isTurn;				//��]�t���O
};