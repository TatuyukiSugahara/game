/*!
 * @brief	�R���C�_�[�B
 */
#pragma once
#include "..\BulletCollision\CollisionShapes\btCollisionShape.h"
	/*!
	 * @brief	�R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
	 */
class ICollider {
public:
	virtual btCollisionShape* GetBody() = 0;
};