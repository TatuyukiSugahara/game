#pragma once
#include "lib\System.h"
#include "Scene\Scene.h"
#include "Camera\Camera.h"
#include "Light\Light.h"
#include "Light\LightBack.h"
#include "Player\Player.h"
#include "Stage.h"
#include "Block\HatenaBox.h"
#include "Gimmick\Kinoko.h"
#include "Block\NBlock.h"
#include "StageBack.h"
#include "Pipe\Pipe.h"
#include "Map.h"
#include "Frame\ShadowMap.h"
#include "Goal\Goal.h"
#include "Enemy\Saboten.h"
#include "Enemy\Mohurun.h"
#include "Sound\SoundSource.h"
#include "Block\NoBlock.h"
#include "Coin\Coin.h"
#include "Goal\GoalFlag.h"
#include "Coin\CoinNomber.h"
#include "Enemy\Bird.h"
#include "Gimmick\RotationGimmick.h"
#include "Coin\CoinGet.h"
#include "Sun.h"
#include "Boss\Boss.h"
#include "Boss\BossLife.h"
#include "Boss\BossName.h"
#include "Boss\BossKatto.h"
#include "Boss\BossClear.h"
#include "Camera\SkyCamera.h"
#include "Enemy\Kame.h"

//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

class CStage : public CScene
{
public:
	CStage(){}
	~CStage()
	{
		for (auto& shape : groundShape){
			delete shape;
		}
		for (auto& rb : rigidBody){
			delete rb;
		}
		delete myMotionState;
		
	}
	void Init();								//������
	void Update();								//�X�V
	void Render();								//�`��
	void UpdateLight();							//���C�g�X�V
	void Release();								//�����[�X
	void CreateCollision();						//�����蔻��
	void AddRigidBody();						//�����蔻��ǉ�
	void BossMusic();							//�{�X�펞�̉��y�Đ��B
	void MusicStop();							//���y�X�g�b�v�B
	void StageChange();							//�f�o�b�O�p�X�e�[�W�ύX�B
	void StageInit();							//�ʏ�X�e�[�W�̏�����
	void StageBossInit();						//�{�X�X�e�[�W�̏�����
	void StageUpdate();							//�ʏ�X�e�[�W�̃A�b�v�f�[�g
	void StageBossUpdate();						//�{�X�X�e�[�W�̃A�b�v�f�[�g
	void StageRender();							//�ʏ�X�e�[�W�̕`��
	void StageBossRender();						//�{�X�X�e�[�W�̕`��
	//�J�������Q�b�g�B
	Camera* GetCamera()
	{
		return&camera;
	}
	//���C�g���Q�b�g�B
	CLight* GetLight()
	{
		return &light;
	}
	//�w�i�p�̃��C�g���Q�b�g�B
	CLightBack* GetLightBack()
	{
		return &lightBack;
	}
	//�v���C���[���Q�b�g�B
	CPlayer* GetPlayer()
	{
		return &player;
	}
	//�L�m�R���Q�b�g�B
	CKinoko* GetKinoko()
	{
		return &kinoko;
	}
	//�͂Ăȃ{�b�N�X���Q�b�g�B
	CHatenaBox* GetHatena()
	{
		return &hanateBox;
	}
	//�}�b�v���Q�b�g
	CMap* GetMap()
	{
		return&map;
	}
	//�e���Q�b�g�B
	CShadowMap* GetShadow()
	{
		return&shadow;
	}
	//�T�{�e�����Q�b�g�B
	CSaboten* GetSabo()
	{
		return &sabo;
	}
	//�m�[�}���u���b�N���Q�b�g�B
	CNBlock* GetNBlock()
	{
		return &nBlock;
	}
	//�y�ǂ��Q�b�g�B
	CPipe* GetPipe()
	{
		return &pipe;
	}
	//�G(���ӂ��)�������ƁB
	CMohurun* GetMohu()
	{
		return &mohurun;
	}
	//�����Ȃ��u���b�N���Q�b�g�B
	CNoBlock* GetNoBlock()
	{
		return&noBlock;
	}
	//�R�C���̃i���o�[���Q�b�g�B
	CCoinNomber* GetCoinNum()
	{
		return &coinNumber;
	}
	//�T�E���h�\�[�X���Q�b�g�B
	CSoundSource* GetSoundSorce()
	{
		return&soundSource;
	}
	//�G(�Ƃ�)���Q�b�g�B
	CBird* GetBird()
	{
		return &bird;
	}
	//�R�C�����Q�b�g�B
	CCoin* GetCoin()
	{
		return &coin;
	}
	//�擾�����R�C���p�̃R�C�����Q�b�g�B
	CCoinGet* GetCoinSprite()
	{
		return &coinGet;
	}
	//�{�X���Q�b�g�B
	CBoss* GetBoss()
	{
		return &boss;
	}
	//�{�X�̖��O���Q�b�g�B
	CBossName* GetBossName()
	{
		return &bossName;
	}
	//�{�X�펞�̃J�b�g�C�����Q�b�g�B
	CBossKatto* GetBossKatto()
	{
		return &bossKatto;
	}
	//�{�X�����j�������̃J�b�g�C�����Q�b�g�B
	CBossClear* GetBossClear()
	{
		return &bossClear;
	}
	//�R���X�g������ꍇ�̋T���Q�b�g
	const CKame* GetKame() const
	{
		return &kame;
	}
	//�T���Q�b�g
	CKame* GetKame()
	{
		return &kame;
	}
protected:
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	static const int				MaxCollision = 100;			//�R���W�����̍ő吔
	btCollisionShape*				groundShape[MaxCollision];	//�n�ʂ̃R���W�����`��B
	btRigidBody*					rigidBody[MaxCollision];	//���́B
	btDefaultMotionState*			myMotionState;				//���[�V�����X�e�[�g
	bool							isAddCollision;				//�R���W�����ǉ��t���O
	SCollisionInfo*					collisionTable;				//�R���W�����e�[�u��
	int								arraySize;					//�T�C�Y
	bool							bossMusic;					//�{�X�펞�̉��y�t���O�B
	LPD3DXSPRITE					sprite;						//�X�v���C�g
	Camera							camera;						//�J�����B
	CSkyCamera						skyCamera;					//��p�J����
	CLight							light;						//���C�g
	CLightBack						lightBack;					//�w�i���C�g
	CPlayer							player;						//�v���C���[
	CHatenaBox						hanateBox;					//�͂Ăȃ{�b�N�X
	CKinoko							kinoko;						//�L�m�R
	CNBlock							nBlock;						//�m�[�}���u���b�N
	CStageBack						stageBack;					//�X�e�[�W�w�i
	CPipe							pipe;						//�y��
	CMap							map;						//�}�b�v�쐻
	CShadowMap						shadow;						//�e
	CGoal							goal;						//�S�[��
	CSaboten						sabo;						//�T�{�e��
	CMohurun						mohurun;					//���t�����G�l�~�[
	CNoBlock						noBlock;					//�����Ȃ��u���b�N
	CCoin							coin;						//�R�C��
	CGoalFlag						goalFlag;					//�S�[����
	CCoinNomber						coinNumber;					//�R�C���i���o�[
	CBird							bird;						//���G�l�~�[
	CRotationGimmick				rotationGimmick;			//��]����M�~�b�N
	CSoundSource					soundSource;				//�T�E���h�\�[�X
	CCoinGet						coinGet;					//�R�C�����擾�����p�̃R�C��
	CSun							sun;						//���z
	CBoss							boss;						//�{�X
	CBossLife						bossLife;					//�{�X���C�t
	CBossName						bossName;					//�{�X���O
	CBossKatto						bossKatto;					//�{�X�o�ꎞ�̃J�b�g�C���B
	CBossClear						bossClear;					//�{�X���j���̃J�b�g�C���B
	CKame							kame;						//�T
};

extern CStage* g_stage;