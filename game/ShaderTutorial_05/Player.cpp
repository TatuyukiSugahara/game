#include "stdafx.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"
#include "Sound\SoundSource.h"
#include "ResultScene.h"

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//������
	D3DXMatrixIdentity(&mWorld);
	position = D3DXVECTOR3(470.0f, 5.0f, 0.0f);		//�����ʒu
	movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����ړ����x
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//�����X�P�[��
	addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	radius = 0.3f;
	friction = 0.2f;
	state = PlayerStay;
}
//�f�X�g���N�^
CPlayer::~CPlayer()
{
	if (normalMap != NULL)
	{
		normalMap->Release();
	}
}
//�������B
void CPlayer::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//�m�[�}���}�b�v���[�h
	HRESULT hr = D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Asset/model/utc_nomal.tga",
		&normalMap);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�w�肵���p�X�����������m�F���Ă��������B", "�G���[", MB_OK);
	}
	//�X�y�L�����}�b�v�����[�h�B
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Asset/model/utc_spec.tga",
		&specularMap
		);
	//D3DXCreateTextureFromFileA�̖߂�l���`�F�b�N�B
	if (FAILED(hr)) {
		//D3DXCreateTextureFromFileA�Ŏ��s�����B
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�w�肵���p�X�����������m�F�����肢���܂��B", "�G���[", MB_OK);
	}
	if (normalMap != NULL) {
		//�@���}�b�v�̓ǂݍ��݂����������̂ŁACSkinModel�ɖ@���}�b�v��ݒ肷��B
		skinmodel.SetNormalMap(normalMap);
	}
	if (specularMap != NULL) {
		//�X�y�L�����}�b�v�̓ǂݍ��݂����������̂ŁACSkinModel�ɃX�y�����}�b�v��ݒ肷��B
		skinmodel.SetSpecularMap(specularMap);
	}
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

	//���f�������[�h�B
	modelData.LoadModelData("Asset/model/Unity.X", &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0, 0.3);
	animation.SetAnimationEndTime(2, 0.79f);
	animation.SetAnimationEndTime(PlayerIsJump, 0.33f);
	animation.SetAnimationEndTime(PlayerJumpNow, 0.016);
	animation.SetAnimationEndTime(PlayerJumpWas, 0.33f);
	animation.SetAnimationLoopFlag(PlayerIsJump, false);
	animation.SetAnimationLoopFlag(PlayerJumpWas, false);


	characterController.Init(0.3f, 1.0f, position);
	characterController.SetGravity(-30.0f);

	//AABB
	CalcAABBSizeFromMesh(modelData.GetOrgMeshFirst(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
	//�^�[��
	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	turn.Initialize();
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(true);
	skinmodel.SetSpecularMap(true);
}
//�X�V�B
void CPlayer::Update()
{
	if (g_pad.IsPress(enButtonB))
	{
		Move(7.5f);//�ړ�
	}
	else
	{
		Move(5.0f);//�ړ�
	}
	
	Jump();//�W�����v
	Died();//���S
	//�V��Ɠ��������H�������������̂�,�͂Ăȃ{�b�N�X�H
	if (characterController.IsCeiling()
		&& characterController.getCollisionObj() == g_stage->GetHatena()->Get2DHatena())
	{
		g_stage->GetHatena()->SetState(hit);
		g_stage->GetKinoko()->SetState(Leave);//�L�m�R�o��
	}
	//�L�m�R�Ƃ����H&&��������ԁH
	if (g_stage->GetKinoko()->GetKinoko() == true && radius == 0.3f)
	{
		D3DXVec3Scale(&Scale, &Scale, 1.5f);
		radius = 0.45;
		//IsIntersect.CollisitionInitialize(&position, radius);//�����蔻�菉����
	}
	characterController.SetMoveSpeed(movespeed);
	characterController.Execute();
	movespeed = characterController.GetMoveSpeed();
	position = characterController.GetPosition();
	//AABB
	m_aabbMax += characterController.GetAdd();
	m_aabbMin += characterController.GetAdd();

	State();//�A�j���[�V������ԕύX

	//B�_�b�V�����̃A�j���[�V�������x
	if (g_pad.IsPress(enButtonB))
	{
		animation.SetAnimationSpeedRate(2.0f);
	}
	else//�ʏ펞
	{
		animation.SetAnimationSpeedRate(1.0f);
	}
	animation.Update(1.0f / 60.0f);
	//���[���h�s��̍X�V�B
	skinmodel.UpdateWorldMatrix(position, rotation, Scale);
}
//�`��B
void CPlayer::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap
	)
{
	skinmodel.Draw(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
//�J���B
void CPlayer::Release()
{
}

void CPlayer::Move(float maxmove)
{
	bool isTurn = false;

	static D3DXVECTOR3 dirX(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 dirZ(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 dirpad(g_pad.GetLStickXF(), 0.0f, g_pad.GetLStickYF());

	

	addmove.x = dirX.x * dirpad.x - dirZ.x * dirpad.z;
	addmove.z = dirX.z * dirpad.x - dirZ.z * dirpad.z;
	
	//�J�����������Ă�������ɐi�ށB
	dirZ = g_stage->GetCamera()->GetCameraDir();
	D3DXVec3Normalize(&addmove, &addmove);
	//�J�����̌����Ă�������ƁA��x�N�g���Ƃ̊O�ς��v�Z����Ɖ��ړ��̃x�N�g�������܂�B
	D3DXVec3Cross(&dirX, &dirZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	if (D3DXVec3Length(&addmove) > 0.0f){
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &addmove));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &forward, &addmove);
		if (axis.x > 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
		isTurn = true;
		m_currentAngleY = turn.Update(isTurn, m_targetAngleY);
		D3DXQuaternionRotationAxis(&rotation, &axis, m_currentAngleY);
	}
	D3DXVECTOR3 v1;//���݂̐i�s����
	D3DXVec3Normalize(&v1, &movespeed);
	D3DXVECTOR3 v2;//���̐i�s����
	D3DXVec3Normalize(&v2, &addmove);
	//����
	float naiseki = D3DXVec3Dot(&v1, &v2);
	//�ړ��ʂ�����Ȃ�
	friction = 0.25f;
	/*if (D3DXVec3Length(&addmove) > 0.0f)
	{
		friction = 0.8f + 2.6f * (1.0f - fabs(naiseki));
	}
	else
	{
		friction = 0.4f;
	}*/

	//���x�����Z�B
	movespeed.x += addmove.x;
	movespeed.z += addmove.z;

	//���x�̏��
	D3DXVECTOR3 moveSpeedXZ = movespeed;
	moveSpeedXZ.y = 0.0f;
	D3DXVec3Normalize(&v1, &moveSpeedXZ);
	/*if (!IsIntersect.GetGround()){
		addmove *= 0.2f;
	}*/
	if (D3DXVec3Length(&moveSpeedXZ) >= maxmove )
	{

		movespeed.x = v1.x * maxmove;
		movespeed.z = v1.z * maxmove;
	}

	
	if (characterController.IsOnGround())
	{
		//�n�ʂňړ���
		D3DXVECTOR3 masatu(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&masatu, &movespeed);
		masatu *= -friction;
		if (D3DXVec3Length(&moveSpeedXZ) < D3DXVec3Length(&masatu))
		{
			masatu = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		movespeed.x += masatu.x;
		movespeed.z += masatu.z;
	}
}

void CPlayer::Jump()
{
	if (g_pad.IsTrigger(EnButton::enButtonA)
		&& state != PlayerIsJump
		&& state != PlayerJumpNow
		)
	{
		if (g_pad.IsPress(EnButton::enButtonB))
		{
			movespeed.y = 18.0f;
		}
		else
		{
			movespeed.y = 15.0f;
		}
		CSoundSource* SEjump = new CSoundSource;
		SEjump->Init("Asset/Sound/jump.wav");
		SEjump->Play(false);
		SEjump->SetVolume(0.25f);
		state = PlayerIsJump;
		animation.PlayAnimation(PlayerIsJump,0.05f);
		characterController.Jump();

	}
}

void CPlayer::State()
{
	//�����Ă��邩�n�ʂɂ��Ă���H
	if (fabs(D3DXVec3Length(&movespeed)) >= 0.1f && characterController.IsOnGround() == true)
	{
		if (state != PlayerRun)
		{
			state = PlayerRun;
			animation.PlayAnimation(PlayerRun, 0.3);
		}
	}
	//�n�ʂɂ��Ă��ē����Ă��Ȃ�
	if (characterController.IsOnGround() == true && fabs(D3DXVec3Length(&movespeed)) <= 0.1f)
	{
		if (state != PlayerStay)
		{
			//���n��
			if (state == PlayerJumpNow)
			{
				state = PlayerJumpWas;
				animation.PlayAnimation(PlayerJumpWas, 0.3f);
				friction = 0.8f;
			}
			//�X�e�C���
			if (!animation.IsPlay() || state == PlayerRun)
			{
				state = PlayerStay;
				animation.PlayAnimation(PlayerStay, 0.3);
				movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

		}
		
	}
	//�W�����v��
	if (!characterController.IsOnGround())
	{
		if (state != PlayerJumpNow && !animation.IsPlay())
		{
			state = PlayerJumpNow;
			animation.PlayAnimation(PlayerJumpNow, 0.2f);
		}
	}
}

void CPlayer::Died()
{
	if (position.y <= -10.0f)
	{
		CSoundSource* SEDeath = new CSoundSource;
		SEDeath->Init("Asset/Sound/death.wav");
		SEDeath->Play(false);
		g_resultscene.SetState(ResultState::Death);
		scene = GameScene::Result;
	}
}

