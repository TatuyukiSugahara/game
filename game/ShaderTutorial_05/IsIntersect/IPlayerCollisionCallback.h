#pragma once

class IPlayerCollisionCallback{
private:
	bool isHitGround;	//’n–Ê
	bool isHitWall;		//•Ç
	bool isHitCeiling;	//“Vˆä
public:
	virtual bool OnHitGroundTrigger(const btCollisionObject*){ return false; }
	virtual void OnHitGroundLeave(const btCollisionObject*){}
	virtual void OnHitGround(const btCollisionObject*){}
	virtual void OnHitWall(const btCollisionObject*){}
	virtual bool OnHitCeilingTrigger(const btCollisionObject*){ return false; }
	virtual void OnHitCeilingLeave(const btCollisionObject*){}
	virtual void OnHitCeiling(const btCollisionObject*){}
	void SetHitGround(bool hit)
	{
		isHitGround = hit;
	}
	void SetHitWall(bool hit)
	{
		isHitWall = hit;
	}
	void SetHitCeiling(bool hit)
	{
		isHitCeiling = hit;
	}
	bool IsHitGround()
	{
		return isHitGround;
	}
	bool IsHitWall()
	{
		return isHitWall;
	}
	bool IsHitCeiling()
	{
		return /*IsHitCeiling()*/true;
	}
};