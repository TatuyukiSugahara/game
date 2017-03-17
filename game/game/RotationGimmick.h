#pragma once

class CRotationGimmick
{
public:
	CRotationGimmick();
	~CRotationGimmick();
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
		*position = pos;
	} 
	//�|�W�V�����Q�b�g
	const D3DXVECTOR3& GetPos() const
	{
		return *position;
	}
private:
	D3DXVECTOR3				originPos;		//���_�̍��W
	D3DXVECTOR3				position[3];	//���W�B
	D3DXVECTOR3				vector;			//����
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				rotation;		//��]�s��B
	SkinModel				skinModel[3];	//�X�L�����f��
	SkinModelData			modelData[3];	//���f���f�[�^
	Animation				animation;		//�A�j���[�V����
	CLight					light;			//���C�g
};

