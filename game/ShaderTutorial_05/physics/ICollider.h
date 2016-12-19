/*!
 * @brief	コライダー。
 */
#pragma once
#include "..\BulletCollision\CollisionShapes\btCollisionShape.h"
	/*!
	 * @brief	コライダーのインターフェースクラス。
	 */
class ICollider {
public:
	virtual btCollisionShape* GetBody() = 0;
};