#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"
#include "character\CharacterController.h"


enum PlayerState{
	PlayerStay,			//ステイ
	PlayerWalk,			//歩く
	PlayerRun,			//走る
	PlayerJump,			//ジャンプ
	PlayerIsJump,		//ジャンプをするとき
	PlayerJumpNow,		//ジャンプ中
	PlayerJumpWas,		//着地時
	PlayerHipDrop,		//ヒップドロップ
};

enum Life{
	Alive,				//生きている
	Died,				//死んだ
};

//プレイヤークラス。
class CPlayer {
public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap
		);
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
		characterController.SetPosition(pos);
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	D3DXVECTOR3 GetMoveSpeed()
	{
		return movespeed;
	}
	/*D3DXVECTOR3 GetAddPos()
	{
		return IsIntersect.GetAddPos();
	}*/
	D3DXVECTOR3 GetAABBMax()
	{
		return m_aabbMaxget;
	}
	D3DXVECTOR3 GetAABBMin()
	{
		return m_aabbMinget;
	}
	D3DXMATRIX GetWMatrix()
	{
		return mWorld;
	}
	D3DXMATRIX GetRot()
	{
		return mRotation;
	}
	/*CIsIntersect GetIsIntersect()
	{
		return IsIntersect;
	}*/
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		skinmodel.SetEffect(effect);
	}
	ID3DXEffect* GetEffect()
	{
		return skinmodel.GetEffect();
	}
	void SetMoveSpeed(D3DXVECTOR3 speed)
	{
		movespeed = speed;
	}
	Life GetLifeState()
	{
		return lifestate;
	}
	void SetLifeState(Life life)
	{
		lifestate = life;
	}
	void SetScale(D3DXVECTOR3 scal)
	{
		Scale = scal;
	}
	D3DXVECTOR3 GetScale()
	{
		return Scale;
	}
	void SubScale(D3DXVECTOR3 sub)
	{
		Scale -= sub;
	}
	void AddScale(D3DXVECTOR3 add)
	{
		Scale += add;
	}
	void Move(float maxmove);
	void Jump();
	void State();
	void Died();//死亡
private:
	D3DXVECTOR3				position;						//座標。
	D3DXVECTOR3				movespeed;						//移動速度
	D3DXVECTOR3				Scale;							//スケールw
	D3DXMATRIX				mWorld;							//ワールド行列。
	D3DXMATRIX				mRotation;						//回転行列。
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	LPDIRECT3DTEXTURE9 normalMap = NULL;					//ノーマルマップ
	LPDIRECT3DTEXTURE9 specularMap = NULL;					//スペキュラマップ。
	CTurn					turn;							//ターンクラス
	CCharacterController characterController;				//キャラクターコントローラー
	const float				MOVE_SPEED = 5.0f;				//移動速度
	float					radius;
	float					friction;						//摩擦
	PlayerState				state;							//プレイヤーの状態
	Life					lifestate;						//プレイヤー生死
	D3DXQUATERNION			rotation;						//回転クォータニオン
	float					deathCount;						//死亡までのカウント
	D3DXVECTOR3				addmove;							//次の移動
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	D3DXVECTOR3 m_aabbMinget;
	D3DXVECTOR3 m_aabbMaxget;
	//ターン
	float					m_currentAngleY;
	float					m_targetAngleY;

	//サウンド
	CSoundSource* SEjump;

};