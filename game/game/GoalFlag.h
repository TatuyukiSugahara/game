#pragma once
class CGoalFlag {
public:
	//�R���X�g���N�^
	CGoalFlag();
	//�f�X�g���N�^
	~CGoalFlag();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
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
};