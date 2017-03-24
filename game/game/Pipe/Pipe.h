#pragma once

//�y�ǃ`�b�v�̔z�u���B
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
* @brief	�y�ǃN���X�B
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
	//�z�u���̃e�[�u���T�C�Y�Q�b�g
	const int& GetSize() const
	{
		return tableSize;
	}
	//�y�ǔz�u���̃e�[�u���T�C�Y�Q�b�g
	const int& GetArraySize() const
	{
		return arraySize;
	}
	//�y�ǂɓ����Ă��邩�t���O�B
	const bool& GetIsPipe() const
	{
		return isPipe;
	}
	//�y�ǂ̍��̃Q�b�g
	const btRigidBody *GetPipe() const
	{
		return *rigidBodypipe;
	}
	//�����蔻��쐬
	void CreateCollision();	
	//�����蔻��ǉ�
	void AddRigidBody();	
	//�����蔻��폜
	void RemoveRigidBody();	
private:
	
	static const int				MAXCOLLISION = 30;				//�R���W�����̏��
	btCollisionShape*				pipeboxShape[MAXCOLLISION];		//�n�ʂ̃R���W�����`��B
	btRigidBody*					rigidBodypipe[MAXCOLLISION];	//���́B
	btDefaultMotionState*			myMotionState;					//���[�V�����X�e�[�g
	bool							isAddCollision;					//�R���W�����ǉ��t���O
	std::vector<CPipeChip*>			pipeChipList;					//�y�ǃ`�b�v�̃��X�g�B
	SPipeChipLocInfo*				pipeChipTable;					//�y�ǃR���W�������̃e�[�u��
	SCollisionInfoPipe*				collisionTablpipe;				//�y�ǔz�u���̃e�[�u��
	int								arraySize;						//�y�ǔz�u���̃e�[�u���T�C�Y
	int								tableSize;						//�z�u���̃e�[�u���T�C�Y
	int								count;							//�y�ǂɓ���J�E���g;
	D3DXVECTOR3						nextPos;						//���̓y�ǂ̏ꏊ;
	bool							isPipe;							//�y�ǂɓ���t���O;
	std::unique_ptr<CSoundSource>	sePipe;
};
