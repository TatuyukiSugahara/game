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
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�傫��
	SkinModel				skinModel;		//���f��
	SkinModelData			modelData;		//���f���f�[�^
	Animation				animation;		//�A�j���[�V����
	CLight					light;			//���C�g
};