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
	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
};