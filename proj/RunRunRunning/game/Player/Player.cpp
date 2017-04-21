#include "stdafx.h"
#include "Player.h"
#include "Frame\CalcAABBSizeFromMesh.h"
#include "Map\Stage.h"
#include "Sound\SoundSource.h"
#include "Result/ResultScene.h"

namespace{
	const float NORMAL_RUN_SPEED = 4.25f;				//通常移動速度
	const float DASH_RUN_SPEED = 9.0f;					//ダッシュ時移動速度
	const float DASH_ANIMATION_SPEED = 2.0f;			//ダッシュ時アニメーション速度
	const float NORMAL_ANIMATION_SPEED = 1.0f;			//通常時アニメーション速度
	const float JUMP_POWER = 18.0f;						//ジャンプ力	
	const float MAX_FALLING_SPEED = -10.0f;				//落下中の上限速度
	const float RUN_FRICTION = 0.25f;					//走っている時の摩擦力
	const float LANDING_FRICTION = 0.8f;				//着地時の摩擦力
	const float HIPDROP_SPEED = 20.0f;					//ヒップドロップ速度
	const float DEAD_TIME = 5.5f;						//死亡する時間
	const float DEAD_TIME_CAMERA = 5.0f;				//死亡する前のカメラ回転する時間
}
//コンストラクタ
CPlayer::CPlayer()
{
	//初期化
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		position = D3DXVECTOR3(1.0f, 5.0f, 0.0f);		//初期位置
		break;
	case CSceneManager::StageNumber::Stage2:
		position = D3DXVECTOR3(1.0f, 205.0f, 0.0f);		//初期位置
		break;
	case CSceneManager::StageNumber::StageBoss:
		position = D3DXVECTOR3(1.0f, 5.0f, 0.0f);		//初期位置
		break;
	}
	moveSpeed = CConst::Vec3Zero;						//初期移動速度
	scale = D3DXVECTOR3(1.4f, 1.4f, 1.4f);				//初期スケール
	addMove = CConst::Vec3Zero;							//移動速度追加初期化
	aabbMax = CConst::Vec3Zero;							//AABB初期化
	aabbMin = CConst::Vec3Zero;							//AABB
	aabbMaxGet = CConst::Vec3Zero;						//AABB初期化
	aabbMinGet = CConst::Vec3Zero;						//AABB初期化
	rate = 0.0f;										//モーフィング用時間
	radius = 0.3f;										//半径初期化
	friction = 0.25f;									//摩擦初期化
	state = PlayerState::Stay;							//プレイヤー状態初期化
	lifeState = Life::Alive;							//生死状態初期化
}
//デストラクタ
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
//初期化。
void CPlayer::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//ノーマルマップロード
	HRESULT hr = D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Asset/model/utc_nomal.tga",
		&normalMap);
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャのロードに失敗しました。指定したパスが正しいか確認してください。", "エラー", MB_OK);
	}
	//スペキュラマップをロード。
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Asset/model/utc_spec.tga",
		&specularMap
		);
	//D3DXCreateTextureFromFileAの戻り値をチェック。
	if (FAILED(hr)) {
		//D3DXCreateTextureFromFileAで失敗した。
		MessageBox(NULL, "テクスチャのロードに失敗しました。指定したパスが正しいか確認をお願いします。", "エラー", MB_OK);
	}
	if (normalMap != NULL) {
		//法線マップの読み込みが成功したので、CskinModelに法線マップを設定する。
		skinModel.SetNormalMap(normalMap);
	}
	if (specularMap != NULL) {
		//スペキュラマップの読み込みが成功したので、CskinModelにスペきゅらマップを設定する。
		skinModel.SetSpecularMap(specularMap);
	}
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//モデルをロード。
	modelData.LoadModelData("Asset/model/Unity.X", &animation);
	modelDataMorpA.LoadModelData("Asset/model/skinModelMorpA.X", NULL);
	modelDataMorpB.LoadModelData("Asset/model/Unity.X", NULL);

	//オリジナル
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	//モーフィング用A
	skinModelMorpA.Init(&modelDataMorpA);
	skinModelMorpA.SetLight(&light);
	//モーフィング用B
	skinModelMorpB.Init(&modelDataMorpB);
	skinModelMorpB.SetLight(&light);

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
	//ターン
	currentAngleY = 0.0f;
	targetAngleY = 0.0f;
	turn.Init();
	skinModel.SetShadowReceiverFlag(false);
	skinModel.SetDrawToShadowMap(true);
	skinModel.SetNormalMap(true);
	skinModel.SetSpecularMap(true);
	skinModel.SetHureneruflg(true);
}
//更新。
void CPlayer::Update()
{

	/*if (GetAsyncKeyState(VK_LEFT)) {
		rate = max(0.0f, rate - 0.03f);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		rate = min(1.0f, rate + 0.03f);
	}
	skinModel.Morphing(&skinModelMorpA, &skinModelMorpB, rate);*/

	if (!g_stage->GetPipe()->GetIsPipe() && !playerStop)
	{
		if (g_pad.IsPress(enButtonB))
		{
			Move(DASH_RUN_SPEED);//移動
		}
		else
		{
			Move(NORMAL_RUN_SPEED);//移動
		}
		Jump();//ジャンプ
	}
	//プレイヤーを静止させるフラグ
	if (playerStop == true)
	{
		//地面についているか
		if (characterController.IsOnGround())
		{
			moveSpeed = CConst::Vec3Zero;//移動速度を0に
		}
	}
	//死亡
	Died();
	//キャラクターコントローラー更新
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	moveSpeed = characterController.GetMoveSpeed();	//移動速度代入
	position = characterController.GetPosition();	//座標代入
	characterController.SetPosition(position);
	//AABB更新
	aabbMaxGet = aabbMax + position;
	aabbMinGet = aabbMin + position;
	//アニメーション状態変更
	State();
	//Bダッシュ時のアニメーション速度
	if (g_pad.IsPress(enButtonB))
	{
		animation.SetAnimationSpeedRate(DASH_ANIMATION_SPEED);
	}
	//通常時
	else
	{
		animation.SetAnimationSpeedRate(NORMAL_ANIMATION_SPEED);
	}
	animation.Update(CConst::DeltaTime);
	//ワールド行列の更新。
	skinModel.UpdateWorldMatrix(position, rotation, scale);
}
//描画。
void CPlayer::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap
	)
{
	skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
//開放。
void CPlayer::Release()
{
}

void CPlayer::Move(float maxmove)
{
	//ターンフラグをfalseに
	bool isTurn = false;
	//方向
	static D3DXVECTOR3 dirX = CConst::Vec3AxisX;
	static D3DXVECTOR3 dirZ = CConst::Vec3AxisZ;
	//パッドの方向
	D3DXVECTOR3 dirpad(g_pad.GetLStickXF(), 0.0f, g_pad.GetLStickYF());
	//カメラの向いている方向と、上ベクトルとの外積を計算すると横移動のベクトルが求まる。
	D3DXVec3Cross(&dirX, &dirZ, &CConst::Vec3Up);
	//移動速度追加
	addMove.x = dirX.x * dirpad.x - dirZ.x * dirpad.z;
	addMove.z = dirX.z * dirpad.x - dirZ.z * dirpad.z;
	//カメラが向いている方向に進む。
	dirZ = g_stage->GetCamera()->GetCameraDir();
	//ノーマライズ
	D3DXVec3Normalize(&addMove, &addMove);
	//移動しているとき
	if (D3DXVec3Length(&addMove) > 0.0f)
	{
		//前方向
		D3DXVECTOR3 front = CConst::Vec3Front;
		//ターゲットのアングル
		targetAngleY = acos(D3DXVec3Dot(&front, &addMove));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &front, &addMove);
		if (axis.x > 0.0f)
		{
			targetAngleY *= -1.0f;
		}
		isTurn = true;
		currentAngleY = turn.Update(isTurn, targetAngleY);
		D3DXQuaternionRotationAxis(&rotation, &axis, currentAngleY);
	}
	D3DXVECTOR3 v1;//現在の進行方向
	D3DXVec3Normalize(&v1, &moveSpeed);
	D3DXVECTOR3 v2;//次の進行方向
	D3DXVec3Normalize(&v2, &addMove);
	//内積
	float naiseki = D3DXVec3Dot(&v1, &v2);
	//移動量があるなら
	friction = RUN_FRICTION;
	//速度を加算。
	moveSpeed.x += addMove.x;
	moveSpeed.z += addMove.z;
	//速度の上限
	D3DXVECTOR3 moveSpeedXZ = moveSpeed;
	//高さはいらない
	moveSpeedXZ.y = 0.0f;
	D3DXVec3Normalize(&v1, &moveSpeedXZ);
	//上限より大きいなら移動速度を代入
	if (D3DXVec3Length(&moveSpeedXZ) >= maxmove )
	{
		//進行方向*移動速度
		moveSpeed.x = v1.x * maxmove;
		moveSpeed.z = v1.z * maxmove;
	}
	//地面で移動中
	if (characterController.IsOnGround())
	{
		//摩擦
		D3DXVECTOR3 masatu = CConst::Vec3Zero;
		D3DXVec3Normalize(&masatu, &moveSpeed);
		//摩擦をかける
		masatu *= -friction;
		//摩擦より移動速度が小さいなら摩擦と移動速度をなくす。
		if (D3DXVec3Length(&moveSpeedXZ) < D3DXVec3Length(&masatu))
		{
			masatu = CConst::Vec3Zero;
			moveSpeed = CConst::Vec3Zero;
		}
		//移動速度を加算
		moveSpeed.x += masatu.x;
		moveSpeed.z += masatu.z;
	}
}

void CPlayer::Jump()
{
	//Aボタンが押されたら
	if (g_pad.IsTrigger(EnButton::enButtonA)
		&& state != PlayerState::IsJump
		&& state != PlayerState::JumpNow
		)
	{
		//ジャンプパワー代入
		moveSpeed.y = JUMP_POWER;
		//サウンド再生
		seJump.reset( new CSoundSource );
		seJump->Init("Asset/Sound/jump.wav");
		seJump->SetVolume(0.25f);
		seJump->Play(false);
		//ステートをジャンプに
		state = PlayerState::IsJump;
		//アニメーション再生
		animation.PlayAnimation((int)PlayerState::IsJump,0.05f);
		//キャラクターコントローラーもジャンプ中に
		characterController.Jump();
	}
	//空中での落下の上限
	//ヒップドロップ中は上限なし
	if (moveSpeed.y <= MAX_FALLING_SPEED && state != PlayerState::HipDrop)
	{
		moveSpeed.y = MAX_FALLING_SPEED;
	}
}

void CPlayer::State()
{
	//動いているかつ地面についている？
	if (fabs(D3DXVec3Length(&moveSpeed)) >= 0.1f && characterController.IsOnGround() == true)
	{
		if (state != PlayerState::Run)
		{
			state = PlayerState::Run;
			animation.PlayAnimation((int)PlayerState::Run, 0.3f);
		}
	}
	//地面についていて動いていない
	if (characterController.IsOnGround() == true && fabs(D3DXVec3Length(&moveSpeed)) <= 0.1f)
	{
		if (state != PlayerState::Stay)
		{
			//着地時
			if (state == PlayerState::JumpNow)
			{
				state = PlayerState::JumpWas;
				animation.PlayAnimation((int)PlayerState::JumpWas, 0.3f);
				friction = LANDING_FRICTION;
			}
			//ステイ状態
			if (!animation.IsPlay() || state == PlayerState::Run)
			{
				state = PlayerState::Stay;
				animation.PlayAnimation((int)PlayerState::Stay, 0.3f);
				//移動しないので移動速度を0に
				moveSpeed = CConst::Vec3Zero;
			}
		}
	}
	//ジャンプ中
	if (!characterController.IsOnGround())
	{
		//ヒップドロップ
		if (g_pad.IsPress(enButtonRB1))
		{
			if (state != PlayerState::HipDrop)
			{
				state = PlayerState::HipDrop;
				animation.PlayAnimation((int)PlayerState::HipDrop, 0.2f);
				//真下に落ちてほしいので移動速度を0に
				moveSpeed = CConst::Vec3Zero;
				//下に速度加算
				moveSpeed.y -= HIPDROP_SPEED;
			}
		}
		//ジャンプ
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
		//死亡時間初期化
		diedTime = 0.0f;
		return;
	}
	diedTime += CConst::DeltaTime;
	//5秒経過するとカメラを上にずらし落下
	if (diedTime > DEAD_TIME_CAMERA)
	{
		static const float Radian5 = D3DXToRadian(-5.0f);
		g_stage->GetCamera()->RotLongitudinal(Radian5);
	}
	//5.5秒経過すると死亡
	if (diedTime > DEAD_TIME)
	{
		lifeState = Life::Died;
	}
	//死亡すると
	if (lifeState == Life::Died)
	{
		//サウンドストップ
		g_stage->GetSoundSorce()->Stop();
		g_scenemanager->SetResult(1);//死んだ場合
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Result);
	}
}

void CPlayer::Clear()
{
	//ボス撃破時のピース。
	if (characterController.IsOnGround() == true && state != PlayerState::Happy)
	{
		playerStop = true;
		//正面を向かせるため
		//回転を初期化
		rotation = CConst::QuaternionIdentity;
		//真正面に回転させる
		D3DXQuaternionRotationAxis(&rotation, &CConst::Vec3Up, D3DX_PI);
		state = PlayerState::Happy;
		animation.PlayAnimation((int)PlayerState::Happy, 0.1f);
		skinModel.Morphing(&skinModelMorpA, &skinModelMorpB, rate);
		rate += 0.001f;
	}
}