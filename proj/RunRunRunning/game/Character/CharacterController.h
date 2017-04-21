/*!
 * @brief	�L�����N�^�R���g���[���[�B
 */

#pragma once

#include "../Physics/SphereCollider.h"
#include "../Physics/CapsuleCollider.h"
#include "../Physics/RigidBody.h"


#define PI 3.14159265358979323846f
	/*!
	 * @brief	�L�����N�^�R���g���[���[�B
	 */
class CCharacterController{
public:
	CCharacterController() {

	}
	~CCharacterController()
	{

	}
	/*!
	 * @brief	�������B
	 */
	void Init(float radius, float height, const D3DXVECTOR3& position);
	/*!
	 * @brief	���s�B
	 */
	void Execute();
	/*!
	 * @brief	���W���擾�B
	 */
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	 * @brief	���W��ݒ�B
	 */
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
	 * @brief	�ړ����x��ݒ�B
	 */
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	 * @brief	�ړ����x���擾�B
	 */
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
	 * @brief	�W�����v������B
	 */
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}
	/*!
	 * @brief	�W�����v��������
	 */
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�n�ʏ�ɂ��邩����B
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	�u���b�N�Ɠ�����������������B
	*/
	bool IsCeiling() const
	{
		return m_isCeiling;
	}
	/*!
	* @brief	�u���b�N�Ɠ�����������������B
	*/
	bool IsKabe() const
	{
		return m_isKabe;
	}
	
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CCapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	�d�͂��擾�B
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	CRigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
	//<!�ǂ̃I�u�W�F�N�g�Ɠ���������?
	const btCollisionObject* getCollisionObj()
	{
		return hitCollisionObject;
	}
private:
	D3DXVECTOR3 			m_position = D3DXVECTOR3(0.0f,0.0f,0.0f);	//���W�B
	D3DXVECTOR3 			m_moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ����x�B
	D3DXVECTOR3				UP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//������̃x�N�g��
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	bool				m_isCeiling = false;			//�u���b�N�Ɠ������������H
	bool				m_isKabe = false;				//�ǂƓ��������H
	CCapsuleCollider	m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;
	float				m_height = 0.0f;
	CRigidBody			m_rigidBody;					//���́B
	float				m_gravity = -9.8f;				//�d�́B
	const btCollisionObject* hitCollisionObject;//�ǂ̃R���W�����Ɠ��������H
};