#pragma once
#include "..\stdafx.h"
	class ICollider;

	//���̏��B
	struct RigidBodyInfo {
		RigidBodyInfo() :
			collider(NULL),
			mass(0.0f)
		{
			pos = D3DXVECTOR3(0.0f,0.0f,0.0f);					//������
			rot = D3DXQUATERNION{ 0.0f, 0.0f, 0.0f, 1.0f };		//������
		}
		D3DXVECTOR3 pos;				//���W�B
		D3DXQUATERNION rot;			//��]�B
		ICollider* collider;		//�R���C�_�[�B
		float mass;					//���ʁB

	};
	//���̃N���X�B
	class CRigidBody
	{
		btRigidBody*			rigidBody;		//���́B
		btDefaultMotionState*	myMotionState;	//���[�V�����X�e�[�g�B
	public:
		CRigidBody();
		~CRigidBody();
		void Release();
		void Create(RigidBodyInfo& rbInfo);
		btRigidBody* GetBody()
		{
			return rigidBody;
		}
	};