#pragma once

class CTurn
{
public:
	CTurn()
	{
	};
	~CTurn();
	//回転処理の初期化
	void CTurn::Init();		
	//回転処理の更新
	float CTurn::Update(bool isTurn, float currentAngleY);
private:
	float	currentAngleY;		//現在の方向
	float	targetAngleY;		//向きたい方向
	float	turnSpeed;			//回転速度
	float   cTurnSpeed;			//ターンスピード
	bool	isTurn;				//回転フラグ
};