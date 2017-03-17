#include "stdafx.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"
#include "Sound\SoundSource.h"
#include "ResultScene.h"

namespace{
	const float NORMAL_RUN_SPEED = 4.25f;				//�ʏ�ړ����x
	const float DASH_RUN_SPEED = 9.0f;					//�_�b�V�����ړ����x
	const float DASH_ANIMATION_SPEED = 2.0f;			//�_�b�V�����A�j���[�V�������x
	const float NORMAL_ANIMATION_SPEED = 1.0f;			//�ʏ펞�A�j���[�V�������x
	const float JUMP_POWER = 18.0f;						//�W�����v��	
	const float MAX_FALLING_SPEED = -10.0f;				//�������̏�����x
	const float RUN_FRICTION = 0.25f;					//�����Ă��鎞�̖��C��
	const float LANDING_FRICTION = 0.8f;				//���n���̖��C��
	const float HIPDROP_SPEED = 20.0f;					//�q�b�v�h���b�v���x
	const float DEAD_TIME = 5.5f;						//���S���鎞��
	const float DEAD_TIME_CAMERA = 5.0f;				//���S����O�̃J������]���鎞��
}
//�R���X�g���N�^
CPlayer::CPlayer()
{
	//������
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		position = D3DXVECTOR3(1.0f, 5.0f, 0.0f);		//�����ʒu
		break;
	case CSceneManager::StageNumber::Stage2:
		position = D3DXVECTOR3(1.0f, 205.0f, 0.0f);		//�����ʒu
		break;
	case CSceneManager::StageNumber::StageBoss:
		position = D3DXVECTOR3(1.0f, 5.0f, 0.0f);		//�����ʒu
		break;
	}
	movespeed = CConst::Vec3Zero;						//�����ړ����x
	scale = D3DXVECTOR3(1.4f, 1.4f, 1.4f);				//�����X�P�[��
	addmove = CConst::Vec3Zero;							//�ړ����x�ǉ�������
	aabbMax = CConst::Vec3Zero;							//AABB������
	aabbMin = CConst::Vec3Zero;							//AABB������
	rate = 0.0f;										//���[�t�B���O�p����
	radius = 0.3f;										//���a������
	friction = 0.25f;									//���C������
	state = PlayerState::Stay;							//�v���C���[��ԏ�����
	lifestate = Life::Alive;							//������ԏ�����
}
//�f�X�g���N�^
CPlayer::~CPlayer()
{
	if (normalMap != NULL)
	{
		normalMap->Release();
	}
	if (specularMap != NULL)
	{
		specularMap->Release();
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
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//���f�������[�h�B
	modelData.LoadModelData("Asset/model/Unity.X", &animation);
	modelDataA.LoadModelData("Asset/model/morphTargetA.X", NULL);
	modelDataB.LoadModelData("Asset/model/morphTargetB.X", NULL);

	//�I���W�i��
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	//���[�t�B���O�pA
	skinmodelA.Init(&modelDataA);
	skinmodelA.SetLight(&light);
	//���[�t�B���O�pB
	skinmodelB.Init(&modelDataB);
	skinmodelB.SetLight(&light);

	animation.PlayAnimation((int)PlayerState::Stay, 0.3f);
	animation.SetAnimationEndTime((int)PlayerState::Run, 0.79f);
	animation.SetAnimationEndTime((int)PlayerState::IsJump, 0.33f);
	animation.SetAnimationEndTime((int)PlayerState::JumpNow, 0.016f);
	animation.SetAnimationEndTime((int)PlayerState::JumpWas, 0.33f);
	animation.SetAnimationEndTime((int)PlayerState::HipDrop, 0.116f);
	animation.SetAnimationLoopFlag((int)PlayerState::IsJump, false);
	animation.SetAnimationLoopFlag((int)PlayerState::JumpWas, false);
	animation.SetAnimationLoopFlag((int)PlayerState::HipDrop, false);
	animation.SetAnimationLoopFlag((int)PlayerState::Happy, true);

	characterController.Init(0.3f, 1.0f, position);
	characterController.SetGravity(-30.0f);

	//AABB
	CalcAABBSizeFromMesh(modelData.GetOrgMeshFirst(), aabbMin, aabbMax);
	aabbMin;
	aabbMax;
	//�^�[��
	currentAngleY = 0.0f;
	targetAngleY = 0.0f;
	turn.Init();
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(true);
	skinmodel.SetNormalMap(true);
	skinmodel.SetSpecularMap(true);
	skinmodel.SetHureneruflg(true);
}
//�X�V�B
void CPlayer::Update()
{

	/*if (GetAsyncKeyState(VK_LEFT)) {
		rate = max(0.0f, rate - 0.03f);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		rate = min(1.0f, rate + 0.03f);
	}
	skinmodel.Morphing(&modelDataA, &modelDataB, rate);*/

	if (!g_stage->GetPipe()->GetIsPipe() && !playerstop)
	{
		if (g_pad.IsPress(enButtonB))
		{
			Move(DASH_RUN_SPEED);//�ړ�
		}
		else
		{
			Move(NORMAL_RUN_SPEED);//�ړ�
		}
		Jump();//�W�����v
	}
	//�v���C���[��Î~������t���O
	if (playerstop == true)
	{
		//�n�ʂɂ��Ă��邩
		if (characterController.IsOnGround())
		{
			movespeed = CConst::Vec3Zero;//�ړ����x��0��
		}
	}
	//���S
	Died();
	//�L�����N�^�[�R���g���[���[�X�V
	characterController.SetMoveSpeed(movespeed);
	characterController.Execute();
	movespeed = characterController.GetMoveSpeed();	//�ړ����x���
	position = characterController.GetPosition();	//���W���
	characterController.SetPosition(position);
	//AABB�X�V
	aabbMaxget = aabbMax + position;
	aabbMinget = aabbMin + position;
	//�A�j���[�V������ԕύX
	State();
	//B�_�b�V�����̃A�j���[�V�������x
	if (g_pad.IsPress(enButtonB))
	{
		animation.SetAnimationSpeedRate(DASH_ANIMATION_SPEED);
	}
	//�ʏ펞
	else
	{
		animation.SetAnimationSpeedRate(NORMAL_ANIMATION_SPEED);
	}
	animation.Update(CConst::DeltaTime);
	//���[���h�s��̍X�V�B
	skinmodel.UpdateWorldMatrix(position, rotation, scale);
}
//�`��B
void CPlayer::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap
	)
{
	skinmodel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
//�J���B
void CPlayer::Release()
{
}

void CPlayer::Move(float maxmove)
{
	//�^�[���t���O��false��
	bool isTurn = false;
	//����
	static D3DXVECTOR3 dirX = CConst::Vec3AxisX;
	static D3DXVECTOR3 dirZ = CConst::Vec3AxisZ;
	//�p�b�h�̕���
	D3DXVECTOR3 dirpad(g_pad.GetLStickXF(), 0.0f, g_pad.GetLStickYF());
	//�J�����̌����Ă�������ƁA��x�N�g���Ƃ̊O�ς��v�Z����Ɖ��ړ��̃x�N�g�������܂�B
	D3DXVec3Cross(&dirX, &dirZ, &CConst::Vec3Up);
	//�ړ����x�ǉ�
	addmove.x = dirX.x * dirpad.x - dirZ.x * dirpad.z;
	addmove.z = dirX.z * dirpad.x - dirZ.z * dirpad.z;
	//�J�����������Ă�������ɐi�ށB
	dirZ = g_stage->GetCamera()->GetCameraDir();
	//�m�[�}���C�Y
	D3DXVec3Normalize(&addmove, &addmove);
	//�ړ����Ă���Ƃ�
	if (D3DXVec3Length(&addmove) > 0.0f)
	{
		//�O����
		D3DXVECTOR3 front = CConst::Vec3Front;
		//�^�[�Q�b�g�̃A���O��
		targetAngleY = acos(D3DXVec3Dot(&front, &addmove));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &front, &addmove);
		if (axis.x > 0.0f)
		{
			targetAngleY *= -1.0f;
		}
		isTurn = true;
		currentAngleY = turn.Update(isTurn, targetAngleY);
		D3DXQuaternionRotationAxis(&rotation, &axis, currentAngleY);
	}
	D3DXVECTOR3 v1;//���݂̐i�s����
	D3DXVec3Normalize(&v1, &movespeed);
	D3DXVECTOR3 v2;//���̐i�s����
	D3DXVec3Normalize(&v2, &addmove);
	//����
	float naiseki = D3DXVec3Dot(&v1, &v2);
	//�ړ��ʂ�����Ȃ�
	friction = RUN_FRICTION;
	//���x�����Z�B
	movespeed.x += addmove.x;
	movespeed.z += addmove.z;
	//���x�̏��
	D3DXVECTOR3 moveSpeedXZ = movespeed;
	//�����͂���Ȃ�
	moveSpeedXZ.y = 0.0f;
	D3DXVec3Normalize(&v1, &moveSpeedXZ);
	//������傫���Ȃ�ړ����x����
	if (D3DXVec3Length(&moveSpeedXZ) >= maxmove )
	{
		//�i�s����*�ړ����x
		movespeed.x = v1.x * maxmove;	
		movespeed.z = v1.z * maxmove;
	}
	//�n�ʂňړ���
	if (characterController.IsOnGround())
	{
		//���C
		D3DXVECTOR3 masatu = CConst::Vec3Zero;
		D3DXVec3Normalize(&masatu, &movespeed);
		//���C��������
		masatu *= -friction;
		//���C���ړ����x���������Ȃ疀�C�ƈړ����x���Ȃ����B
		if (D3DXVec3Length(&moveSpeedXZ) < D3DXVec3Length(&masatu))
		{
			masatu = CConst::Vec3Zero;
			movespeed = CConst::Vec3Zero;
		}
		//�ړ����x�����Z
		movespeed.x += masatu.x;
		movespeed.z += masatu.z;
	}
}

void CPlayer::Jump()
{
	//A�{�^���������ꂽ��
	if (g_pad.IsTrigger(EnButton::enButtonA)
		&& state != PlayerState::IsJump
		&& state != PlayerState::JumpNow
		)
	{
		//�W�����v�p���[���
		movespeed.y = JUMP_POWER;
		//�T�E���h�Đ�
		SEjump.reset( new CSoundSource );
		SEjump->Init("Asset/Sound/jump.wav");
		SEjump->SetVolume(0.25f);
		SEjump->Play(false);
		//�X�e�[�g���W�����v��
		state = PlayerState::IsJump;
		//�A�j���[�V�����Đ�
		animation.PlayAnimation((int)PlayerState::IsJump,0.05f);
		//�L�����N�^�[�R���g���[���[���W�����v����
		characterController.Jump();
	}
	//�󒆂ł̗����̏��
	//�q�b�v�h���b�v���͏���Ȃ�
	if (movespeed.y <= MAX_FALLING_SPEED && state != PlayerState::HipDrop)
	{
		movespeed.y = MAX_FALLING_SPEED;
	}
}

void CPlayer::State()
{
	//�����Ă��邩�n�ʂɂ��Ă���H
	if (fabs(D3DXVec3Length(&movespeed)) >= 0.1f && characterController.IsOnGround() == true)
	{
		if (state != PlayerState::Run)
		{
			state = PlayerState::Run;
			animation.PlayAnimation((int)PlayerState::Run, 0.3f);
		}
	}
	//�n�ʂɂ��Ă��ē����Ă��Ȃ�
	if (characterController.IsOnGround() == true && fabs(D3DXVec3Length(&movespeed)) <= 0.1f)
	{
		if (state != PlayerState::Stay)
		{
			//���n��
			if (state == PlayerState::JumpNow)
			{
				state = PlayerState::JumpWas;
				animation.PlayAnimation((int)PlayerState::JumpWas, 0.3f);
				friction = LANDING_FRICTION;
			}
			//�X�e�C���
			if (!animation.IsPlay() || state == PlayerState::Run)
			{
				state = PlayerState::Stay;
				animation.PlayAnimation((int)PlayerState::Stay, 0.3f);
				//�ړ����Ȃ��̂ňړ����x��0��
				movespeed = CConst::Vec3Zero;
			}
		}
	}
	//�W�����v��
	if (!characterController.IsOnGround())
	{
		//�q�b�v�h���b�v
		if (g_pad.IsPress(enButtonRB1))
		{
			if (state != PlayerState::HipDrop)
			{
				state = PlayerState::HipDrop;
				animation.PlayAnimation((int)PlayerState::HipDrop, 0.2f);
				//�^���ɗ����Ăق����̂ňړ����x��0��
				movespeed = CConst::Vec3Zero;
				//���ɑ��x���Z
				movespeed.y -= HIPDROP_SPEED;
			}
		}
		//�W�����v
		else
		{
			if (state != PlayerState::JumpNow && !animation.IsPlay())
			{
				state = PlayerState::JumpNow;
				animation.PlayAnimation((int)PlayerState::JumpNow, 0.2f);
			}
		}
	}
	
}

void CPlayer::Died()
{
	if (characterController.IsOnGround() == true)
	{
		//���S���ԏ�����
		diedTime = 0.0f;
		return;
	}
	diedTime += CConst::DeltaTime;
	//5�b�o�߂���ƃJ��������ɂ��炵����
	if (diedTime > DEAD_TIME_CAMERA)
	{
		static const float Radian5 = D3DXToRadian(-5.0f);
		g_stage->GetCamera()->RotLongitudinal(Radian5);
	}
	//5.5�b�o�߂���Ǝ��S
	if (diedTime > DEAD_TIME)
	{
		lifestate = Life::Died;
	}
	//���S�����
	if (lifestate == Life::Died)
	{
		//�T�E���h�X�g�b�v
		g_stage->GetSoundSorce()->Stop();
		g_scenemanager->SetResult(1);//���񂾏ꍇ
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Result);
	}
}

void CPlayer::Clear()
{
	//�{�X���j���̃s�[�X�B
	if (characterController.IsOnGround() == true && state != PlayerState::Happy)
	{
		playerstop = true;
		//���ʂ��������邽��
		//��]��������
		rotation = CConst::QuaternionIdentity;
		//�^���ʂɉ�]������
		D3DXQuaternionRotationAxis(&rotation, &CConst::Vec3Up, D3DX_PI);
		state = PlayerState::Happy;
		animation.PlayAnimation((int)PlayerState::Happy, 0.1f);
		skinmodel.Morphing(&modelDataA, &modelDataB, rate);
		rate += 0.1f;
	}
}