/*!
 * @brief	���̃R���C�_�[�B
 */

#pragma once

#include "ICollider.h"
#include "..\BulletCollision\CollisionShapes\btSphereShape.h"

class CSphereCollider : public ICollider
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CSphereCollider();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CSphereCollider();
	/*!
	 * @brief	���̃R���C�_�[���쐬�B
	 */
	void Create(const float radius);
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btSphereShape*		shape;
};