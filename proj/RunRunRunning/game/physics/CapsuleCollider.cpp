/*!
 * @brief	カプセルコライダー。
 */

#include "../Tk/tkEnginePreCompile.h"
#include "CapsuleCollider.h"

	/*!
	 * @brief	コンストラクタ。
	 */
	CCapsuleCollider::CCapsuleCollider() :
		shape(nullptr)
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CCapsuleCollider::~CCapsuleCollider()
	{
		delete shape;
	}