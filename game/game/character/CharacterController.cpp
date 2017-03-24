/*!
* @brief	�L�����N�^�̃R���W�����R���g���[���B
*/
#include "../stdafx.h"
#include "../Tk/tkEnginePreCompile.h"
#include "CharacterController.h"
#include "CollisionAttr.h"
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			const btCollisionObject* hitCollisionObject = NULL;		//�Փ˂����R���W�����I�u�W�F�N�g
			bool isHit = false;									//�Փ˃t���O�B
			D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
			D3DXVECTOR3 startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);					//���C�̎n�_�B
			D3DXVECTOR3 hitNormal = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�Փ˓_�̖@���B
			btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
			float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

																//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
					) {
					//�����ɏՓ˂����Bor �L�����N�^�����̃R���W�����ƏՓ˂����B
					return 0.0f;
				}
				//�Փ˓_�̖@�������������Ă���B
				D3DXVECTOR3 hitNormalTmp = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
				//������Ɩ@���̂Ȃ��p�x�����߂�B
				float angle = D3DXVec3Dot(&hitNormalTmp, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
				angle = fabsf(acosf(angle));
				if (angle < PI * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
					) {
					//�Փ˂��Ă���B
					isHit = true;
					D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;
					//�Փ˓_�̋��������߂�B�B
					D3DXVECTOR3 vDist;
					vDist = hitPosTmp - startPos;
					float distTmp = D3DXVec3Length(&vDist);
					if (dist > distTmp) {
						//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
						hitPos = hitPosTmp;
						hitNormal = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
						hitCollisionObject = convexResult.m_hitCollisionObject;
						dist = distTmp;
					}
				}
				return 0.0f;
			}
		};
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
		struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
		{
			const btCollisionObject* hitCollisionObject = NULL;	//�Փ˂����R���W�����I�u�W�F�N�g
			bool isHit = false;						//�Փ˃t���O�B
			D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�Փ˓_�B
			D3DXVECTOR3 startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//���C�̎n�_�B
			float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
			D3DXVECTOR3 hitNormal = D3DXVECTOR3(0.0f,0.0f,0.0f);	//�Փ˓_�̖@���B
			btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me) {
					//�����ɏՓ˂����Bor �n�ʂɏՓ˂����B
					return 0.0f;
				}
				//�Փ˓_�̖@�������������Ă���B
				D3DXVECTOR3 hitNormalTmp;
				hitNormalTmp = (D3DXVECTOR3)convexResult.m_hitNormalLocal;
				//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
				float angle = fabsf(acosf(D3DXVec3Dot(&hitNormalTmp, &D3DXVECTOR3(0.0f, 1.0f, 0.0f))));
				if (angle >= PI * 0.3f		//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character	//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
					) {
					isHit = true;
					D3DXVECTOR3 hitPosTmp;
					hitPosTmp = D3DXVECTOR3(convexResult.m_hitPointLocal);
					//��_�Ƃ̋����𒲂ׂ�B
					D3DXVECTOR3 vDist;
					vDist = hitPosTmp - startPos;
					vDist.y = 0.0f;
					float distTmp = D3DXVec3Length(&vDist);
					if (distTmp < dist) {
						//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
						hitPos = hitPosTmp;
						dist = distTmp;
						hitNormal = hitNormalTmp;
						hitCollisionObject = convexResult.m_hitCollisionObject;
					}
				}
				return 0.0f;
			}
			
		};
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�V��p)
		struct SweepResultCeiling : public btCollisionWorld::ConvexResultCallback
		{
			const btCollisionObject* hitCollisionObject = NULL;	//�Փ˂����R���W�����I�u�W�F�N
			bool isHit = false;									//�Փ˃t���O�B
			D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�Փ˓_�B
			D3DXVECTOR3 startPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//���C�̎n�_�B
			D3DXVECTOR3 hitNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�Փ˓_�̖@���B
			btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
			float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

			//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				
				//�Փ˓_�̖@�������������Ă���B
				D3DXVECTOR3 hitNormalTmp = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;

				D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
				float d = D3DXVec3Dot(&hitNormalTmp, &Up);
				if (d > 0.0f) {
					//�������ĂȂ��B
					return 0.0f;
				}
				//������Ɩ@���̂Ȃ��p�x�����߂�B
				float angle = D3DXVec3Dot(&hitNormalTmp, &D3DXVECTOR3(0.0f, -1.0f, 0.0f));
				angle = fabsf(acosf(angle));
				if (angle > 0.9f)		//�ǔ���
				{
					return 0.0f;
				}
				//�Փ˂��Ă���B
				isHit = true;
				D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;
				//�Փ˓_�̋��������߂�B�B
				D3DXVECTOR3 vDist;
				vDist = hitPosTmp - startPos;
				float distTmp = D3DXVec3Length(&vDist);
				if (dist > distTmp) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					hitNormal = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
					hitCollisionObject = convexResult.m_hitCollisionObject;
					dist = distTmp;
				}
				return 0.0f;
			}
			//virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			//{
			//	if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//		//�����B
			//		return 0.0f;
			//	}
			//	D3DXVECTOR3 hitPointNormal;

			//	hitPointNormal.x = convexResult.m_hitNormalLocal.x();
			//	hitPointNormal.y = convexResult.m_hitNormalLocal.y();
			//	hitPointNormal.z = convexResult.m_hitNormalLocal.z();

			//	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

			//	float d = D3DXVec3Dot(&hitPointNormal, &Up);
			//	if (d > 0.0f) {
			//		//�������ĂȂ��B
			//		return 0.0f;
			//	}
			//	if (acosf(d) < PI * 0.2) {
			//		//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			//		return 0.0f;
			//	}
			//	isHit = true;

			//	hitPos.x = convexResult.m_hitPointLocal.x();
			//	hitPos.y = convexResult.m_hitPointLocal.y();
			//	hitPos.z = convexResult.m_hitPointLocal.z();
			//	hitCollisionObject = convexResult.m_hitCollisionObject;
			//	return 0.0f;

			//}
		};


	void CCharacterController::Init(float radius, float height, const D3DXVECTOR3& position)
	{
		m_position = position;
		//�R���W�����쐬�B
		m_radius = radius;
		m_height = height;							
		m_collider.Create(radius, height);			//�R���C�_�[�N���G�C�g
		
		//���̂��������B
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_collider;
		rbInfo.mass = 0.0f;
		m_rigidBody.Create(rbInfo);
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		//g_physicsWorld->AddRigidBody(&m_rigidBody);

	}
	void CCharacterController::Execute()
	{
		//���x�ɏd�͉����x��������B
		m_moveSpeed.y += m_gravity * CConst::DeltaTime;
		//���̈ړ���ƂȂ���W���v�Z����B
		D3DXVECTOR3 nextPosition = m_position;
		//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
		D3DXVECTOR3 addPos = m_moveSpeed;
		addPos *= CConst::DeltaTime;
		nextPosition += addPos;
		D3DXVECTOR3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		D3DXVec3Normalize(&originalXZDir, &originalXZDir);
		//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
		{
			m_isKabe = false;
			int loopCount = 0;
			while (true) {
				//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
				D3DXVECTOR3 addPos;
				addPos = nextPosition - m_position;
				D3DXVECTOR3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (D3DXVec3Length(&addPosXZ) < FLT_EPSILON) {
					//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
					//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
					//�ƂĂ��������l�̂��Ƃł��B
					break;
				}
				//�J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				D3DXVECTOR3 posTmp = m_position;
				posTmp.y += m_height * 0.5f + m_radius + 0.2f;
				//���C���쐬�B
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
				end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

				SweepResultWall callback;
				callback.me = m_rigidBody.GetBody();
				callback.startPos = posTmp;
				//�Փˌ��o�B
				g_physicsWorld->ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

				if (callback.isHit) {
					//���������B
					//�ǁB
					m_isKabe = true;
					hitCollisionObject = callback.hitCollisionObject;//�ǂ̃R���W�����I�u�W�F�N�g�Ɠ��������B
					D3DXVECTOR3 vT0, vT1;
					//XZ���ʏ�ł̈ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
					vT0 = D3DXVECTOR3(nextPosition.x, 0.0f, nextPosition.z);
					vT1 = D3DXVECTOR3(callback.hitPos.x, 0.0f, callback.hitPos.z);
					//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
					D3DXVECTOR3 vMerikomi;
					vMerikomi = vT0 - vT1;
					//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B�B
					D3DXVECTOR3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					D3DXVec3Normalize(&hitNormalXZ, &hitNormalXZ);
					//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
					float fT0 = D3DXVec3Dot(&hitNormalXZ, &vMerikomi);
					//�����߂��Ԃ��x�N�g�������߂�B
					//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
					D3DXVECTOR3 vOffset;
					vOffset = hitNormalXZ;
					vOffset *= (-fT0 + m_radius);
					nextPosition += vOffset;
					D3DXVECTOR3 currentDir;
					currentDir = nextPosition - m_position;
					currentDir.y = 0.0f;
					D3DXVec3Normalize(&currentDir, &currentDir);
					if (D3DXVec3Dot(&currentDir, &originalXZDir) < 0.0f) {
						//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
						//�ړ��悪�t�����ɂȂ�����ړ����L�����Z������B
						nextPosition.x = m_position.x;
						nextPosition.z = m_position.z;
						break;
					}
				}
				else {
					//�ǂ��Ƃ�������Ȃ��̂ŏI���B
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
		//XZ�̈ړ��͊m��B
		m_position.x = nextPosition.x;
		m_position.z = nextPosition.z;

		//������𒲂ׂ�B
#if 1
		m_isCeiling = false;
		{
			D3DXVECTOR3 addPos(0.0f, 0.0f, 0.0f);
			addPos = nextPosition - m_position;
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			btVector3 btStart = btVector3(m_position.x, m_position.y, m_position.z);
			start.setOrigin(btStart);

			SweepResultCeiling callback;
			if (addPos.y > 0.0f){
				if (fabsf(addPos.y) > 0.0001f) {
					end.setOrigin(btVector3(nextPosition.x, nextPosition.y, nextPosition.z));
					callback.me = m_rigidBody.GetBody();
					callback.startPos = D3DXVECTOR3(btStart);
					//�Փˌ��o�B
					g_physicsWorld->ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
				}
				if (callback.isHit) {
					//���������B
					//�V��B
					m_isCeiling = true;
					hitCollisionObject = callback.hitCollisionObject;
					m_moveSpeed.y = 0.0f;
					nextPosition.y = callback.hitPos.y - m_height;
				}
			}
		}
#endif

		//�������𒲂ׂ�B
		{

			D3DXVECTOR3 addPos;
			addPos = nextPosition - m_position;

			m_position = nextPosition;	//�ړ��̉��m��B
			
			if (addPos.y < 0.0f){
				//���C���쐬����B
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
				start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
				//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
				//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
				//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
				D3DXVECTOR3 endPos;
				endPos = D3DXVECTOR3(start.getOrigin());
				endPos.y += addPos.y;
				end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
				SweepResultGround callback;
				callback.me = m_rigidBody.GetBody();
				callback.startPos = D3DXVECTOR3(start.getOrigin());
				if (fabsf(start.getOrigin().y() - endPos.y) > 0.0f) {
					//�Փˌ��o�B
					g_physicsWorld->ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
					if (callback.isHit) {
						//���������B
						hitCollisionObject = callback.hitCollisionObject;	//�n�ʂ̃R���W�����I�u�W�F�N�g�Ɠ��������B
						m_moveSpeed.y = 0.0f;
						m_isJump = false;
						m_isOnGround = true;
						nextPosition.y = callback.hitPos.y;
					}
					else {
						//�n�ʏ�ɂ��Ȃ��B
						m_isOnGround = false;
						m_isJump = true;
					}
				}
			}
		}

		//�ړ��m��B
		m_position = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	}
	/*!
	* @brief	���S�������Ƃ�ʒm�B
	*/
	//void CCharacterController::RemoveRigidBoby()
	//{
	//	//g_physicsWorld->RemoveRigidBody(&m_rigidBody);
	//}