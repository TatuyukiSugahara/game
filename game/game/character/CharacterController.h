/*!
 * @brief	キャラクタコントローラー。
 */

#pragma once

#include "../Physics/SphereCollider.h"
#include "../Physics/CapsuleCollider.h"
#include "../Physics/RigidBody.h"


#define PI 3.14159265358979323846f
	/*!
	 * @brief	キャラクタコントローラー。
	 */
class CCharacterController{
public:
	CCharacterController() {

	}
	~CCharacterController()
	{

	}
	/*!
	 * @brief	初期化。
	 */
	void Init(float radius, float height, const D3DXVECTOR3& position);
	/*!
	 * @brief	実行。
	 */
	void Execute();
	/*!
	 * @brief	座標を取得。
	 */
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	 * @brief	座標を設定。
	 */
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
	 * @brief	移動速度を設定。
	 */
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	 * @brief	移動速度を取得。
	 */
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
	 * @brief	ジャンプさせる。
	 */
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}
	/*!
	 * @brief	ジャンプ中か判定
	 */
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	地面上にいるか判定。
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	ブロックと頭が当たったか判定。
	*/
	bool IsCeiling() const
	{
		return m_isCeiling;
	}
	/*!
	* @brief	ブロックと頭が当たったか判定。
	*/
	bool IsKabe() const
	{
		return m_isKabe;
	}
	
	/*!
	* @brief	コライダーを取得。
	*/
	CCapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	重力を取得。
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}
	/*!
	* @brief	剛体を取得。
	*/
	CRigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();
	//<!どのオブジェクトと当たったか?
	const btCollisionObject* getCollisionObj()
	{
		return hitCollisionObject;
	}
private:
	D3DXVECTOR3 			m_position = D3DXVECTOR3(0.0f,0.0f,0.0f);	//座標。
	D3DXVECTOR3 			m_moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動速度。
	D3DXVECTOR3				UP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//上方向のベクトル
	bool 				m_isJump = false;				//ジャンプ中？
	bool				m_isOnGround = true;			//地面の上にいる？
	bool				m_isCeiling = false;			//ブロックと頭があたった？
	bool				m_isKabe = false;				//壁と当たった？
	CCapsuleCollider	m_collider;						//コライダー。
	float				m_radius = 0.0f;
	float				m_height = 0.0f;
	CRigidBody			m_rigidBody;					//剛体。
	float				m_gravity = -9.8f;				//重力。
	const btCollisionObject* hitCollisionObject;//どのコリジョンと当たった？
};