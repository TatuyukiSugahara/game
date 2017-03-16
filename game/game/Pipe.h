#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SPipeChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�傫��	
};

//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfoPipe {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//�y�ǂɓ��������̏����B
	void InPipe();
	//�y�ǈړ�
	void PipeMove(int now, int next, int pipenum);
	const int& GetSize() const
	{
		return tableSize;
	}
	const int& GetArraySize() const
	{
		return arraySize;
	}
	//�y�ǂɓ����Ă��邩�t���O�B
	const bool& GetIsPipe() const
	{
		return isPipe;
	}
	const btRigidBody *Get2DPipe() const
	{
		return *m_rigidBody2Dpipe;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody(int arraySize);		//2D�����蔻��ǉ�
	void Remove2DRigidBody(int arraySize);	//2D�����蔻��폜
private:
	std::vector<CPipeChip*> pipeChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
	static const int MAXCOLLISION = 30;			//�R���W�����̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_pipeboxShape[MAXCOLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dpipe[MAXCOLLISION];	//����3D�B
	btRigidBody*		m_rigidBody2Dpipe[MAXCOLLISION];	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
	SPipeChipLocInfo* pipeChipTable;
	SCollisionInfoPipe* collisionTablpipe;
	int arraySize;
	int count;								//�y�ǂɓ���J�E���g;
	D3DXVECTOR3			nextPos;			//���̓y�ǂ̏ꏊ;
	bool				isPipe;				//�y�ǂɓ���t���O;
	std::unique_ptr<CSoundSource> SEPipe;
};
