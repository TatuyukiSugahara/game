#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include <vector>
class IPlayerCollisionCallback;
//�����蔻��

#define PI 3.14159265358979323846f

class CIsIntersect
{
public:
	CIsIntersect();
	~CIsIntersect();
	void CollisitionInitialize(D3DXVECTOR3* m_position,float radius);
	void Intersect(
		D3DXVECTOR3* m_position, 
		D3DXVECTOR3* m_moveSpeed, 
		std::vector<IPlayerCollisionCallback*>& callbackList
	);
	D3DXVECTOR3 GetAddPos()
	{
		return addPos;
	}
	bool gethit()
	{
		return isHit;
	}
	bool GetWall()
	{
		return isWall;
	}
	bool GetGround()
	{
		return isGround;
	}
	const btCollisionObject* getCollisionObj()
	{
		return hitCollisionObject;
	}
private:
	float	m_radius;		//���W�A���̊p�x
	//D3DXVECTOR3 m_position;	//�|�W�V����
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	D3DXVECTOR3 addPos;				//�ړ�������
	D3DXVECTOR3 gravity;
	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	bool isHit;					//�V��Ɠ��������H
	bool isWall;				//�ǂƓ��������H
	bool isGround;				//���Ɠ������Ă���H
	const btCollisionObject* hitCollisionObject;//�ǂ̃R���W�����Ɠ��������H

};