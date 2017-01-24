#pragma once

#define MAXCOLLISION 30

class CPipeChip;

/*!
* @brief	�}�b�v�N���X�B
*/
class CPipe {
public:

	CPipe();
	~CPipe();
	void Init();
	void Update();
	//�`��B
	void Render();
	//�y�ǈړ�
	void PipeMove(int now, int next, int pipenum);
	int GetSize()
	{
		return tableSize;
	}
	int GetArraySize()
	{
		return arraySize;
	}
	btRigidBody *Get2DPipe()
	{
		return *m_rigidBody2Dpipe;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody(int arraySize);		//2D�����蔻��ǉ�
	void Remove2DRigidBody(int arraySize);	//2D�����蔻��폜
private:
	std::vector<CPipeChip*> pipeChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_pipeboxShape[MAXCOLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dpipe[MAXCOLLISION];	//����3D�B
	btRigidBody*		m_rigidBody2Dpipe[MAXCOLLISION];	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;

	int arraySize;
	int count;								//�y�ǂɓ���J�E���g;
	D3DXVECTOR3			nextPos;			//���̓y�ǂ̏ꏊ;
	bool				isPipe;				//�y�ǂɓ���t���O;
};
