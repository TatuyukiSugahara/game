#include "stdafx.h"
#include "Kame.h"
#include "Stage.h"
#include "BallCollision.h"

namespace
{
	const float HANSYA = -1.0f;
}

//�R���X�g���N�^
CKame::CKame()
{
	//�������B
	position = D3DXVECTOR3(10.82f, 3.0f, 0.0f);
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;
	moveSpeed = CConst::Vec3Zero;
}
//�f�X�g���N�^
CKame::~CKame()
{
}
//�������B
void CKame::Init()
{
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//���f�������[�h�B
	modelData.LoadModelData("Asset/model/koura.X", NULL);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	//�L�����N�^�[�R���g���[���[������
	CharConInit();
}
//�X�V�B
void CKame::Update()
{
	//�����蔻��
	Hit();
	//�L�����N�^�[�R���g���[���[�X�V
	CharConUpdate();
	//���[���h�s��̍X�V�B
	skinModel.UpdateWorldMatrix(position, rotation, scale);
}
//�`��B
void CKame::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool shadow
	)
{
	skinModel.Render(&viewMatrix, &projMatrix, shadow);
}

void CKame::CharConInit()
{
	characterController.Init(RADIUS, HEIGHT, position);
	characterController.SetGravity(-50.0f);
}

void CKame::CharConUpdate()
{
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	moveSpeed = characterController.GetMoveSpeed();
	position = characterController.GetPosition();
	characterController.SetPosition(position);
}

void CKame::Hit()
{
	if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.5f, 0.3f))
	{
		//�v���C���[�Ɠ����������̕����𒲂ׂ�
		D3DXVECTOR3 Dir = position - g_stage->GetPlayer()->GetPos();
		//Y�����͂���Ȃ�����0
		Dir.y = 0.0f;
		//�����𐳋K������
		D3DXVec3Normalize(&Dir, &Dir);
		//����*�X�s�[�h�ňړ����x������
		moveSpeed = Dir * SPEED;
	}
	//�ǂƓ����������͔��˂���
	if (characterController.IsKabe() == true)
	{
		moveSpeed *= HANSYA;
	}
}