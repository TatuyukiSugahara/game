#pragma once
class CGoal {
public:
	//�R���X�g���N�^
	CGoal();
	//�f�X�g���N�^
	~CGoal();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	//AABB�͈̔͂ɓ����Ă��邩�B
	void AabbUpdate();
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
private:
	D3DXVECTOR3		position;		//���W
	D3DXVECTOR3		scale;			//�傫��
	SkinModel		skinModel;		//���f��	
	SkinModelData	modelData;		//���f���f�[�^
	Animation		animation;		//�A�j���[�V����
	CLight			light;			//���C�g
	D3DXVECTOR3		aabbMin;		//AABB�̍ŏ�
	D3DXVECTOR3		aabbMax;		//AABB�̍ő�
};