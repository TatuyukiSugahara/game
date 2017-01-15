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
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		*position = pos;
	}
	D3DXVECTOR3 GetPos()
	{
		return *position;
	}
private:
	D3DXVECTOR3				originPos;		//���_�̍��W
	D3DXVECTOR3				position[3];	//���W�B�B
	D3DXVECTOR3				vector;			//����
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	SkinModel skinmodel[3];
	SkinModelData modelData[3];
	Animation animation;
	CLight	light;
};

