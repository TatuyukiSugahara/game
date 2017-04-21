#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Frame\Turn.h"
#include "character\CharacterController.h"

//プレイヤークラス。
class CPlayer {
public:
	enum class PlayerState {
		Stay,			//ステイ
		Walk,			//歩く
		Run,			//走る
		Jump,			//ジャンプ
		IsJump,			//ジャンプをするとき
		JumpNow,		//ジャンプ中
		JumpWas,		//着地時
		HipDrop,		//ヒップドロップ
		Happy,			//喜ぶ
	};
	enum class Life{
		Alive,				//生きている
		Died,				//死んだ
	};
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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap
		);
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
		characterController.SetPosition(pos);
	}
	//ポジションゲット
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	} 
	//移動速度ゲット
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return moveSpeed;
	}
	//プレイヤーのAABBのMAXをゲット
	const D3DXVECTOR3& GetAABBMax() const
	{
		return aabbMaxGet;
	}
	//プレイヤーのAABBのMINをゲット
	const D3DXVECTOR3& GetAABBMin() const
	{
		return aabbMinGet;
	}
	//プレイヤーのキャラクターコントローラーゲット
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	//effectセット。
	void SetEffect(ID3DXEffect* effect)
	{
		skinModel.SetEffect(effect);
	}
	//エフェクトゲット
	const ID3DXEffect* GetEffect() const
	{
		return skinModel.GetEffect();
	}
	//移動速度セット
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		moveSpeed = speed;
	}
	//プレイヤーライフステートゲット
	const Life& GetLifeState() const
	{
		return lifeState;
	}
	//ライフステートセット
	void SetLifeState(const Life& life)
	{
		lifeState = life;
	}
	//スケールセット
	void SetScale(const D3DXVECTOR3& scal)
	{
		scale = scal;
	}
	//スケールゲット
	const D3DXVECTOR3& GetScale() const
	{
		return scale;
	}
	//スケール引き算
	void SubScale(const D3DXVECTOR3& sub)
	{
		scale -= sub;
	}
	//スケール足し算
	void AddScale(const D3DXVECTOR3& add)
	{
		scale += add;
	}
	//プレイヤーステートセット
	void SetState(const PlayerState& state)
	{
		this->state = state;
	}
	//プレイヤーを静止させるフラグセット
	void SetPlyaerStop(const bool& stop)
	{
		playerStop = stop;
	}
	//プレイヤー静止させるフラグゲット
	const bool& GetPlayerStop() const
	{
		return playerStop;
	}
	//死亡時間セット
	void SetDiedTime(const float& time)
	{
		diedTime = time;
	}
	//プレイヤー移動関数
	void Move(float maxmove);
	//プレイヤージャンプ関数
	void Jump();
	//プレイヤーのステート関数
	void State();
	//死亡関数
	void Died();
	//クリア時関数		
	void Clear();		
private:
	D3DXVECTOR3						position;						//座標。
	D3DXVECTOR3						moveSpeed;						//移動速度
	D3DXVECTOR3						scale;							//スケールw
	SkinModel						skinModel;						//オリジナル
	SkinModel						skinModelMorpA;						//モーフィング用A
	SkinModel						skinModelMorpB;						//モーフィング用B
	SkinModelData					modelData;						//オリジナル
	SkinModelData					modelDataMorpA;						//モーフィング用A
	SkinModelData					modelDataMorpB;						//モーフィング用B
	Animation 						animation;						//アニメーション
	CLight							light;							//ライト
	LPDIRECT3DTEXTURE9				normalMap = NULL;				//ノーマルマップ
	LPDIRECT3DTEXTURE9				specularMap = NULL;				//スペキュラマップ。
	CTurn							turn;							//ターンクラス
	CCharacterController			characterController;			//キャラクターコントローラー
	PlayerState						state;							//プレイヤーの状態
	Life							lifeState;						//プレイヤー生死
	D3DXQUATERNION					rotation;						//回転クォータニオン
	D3DXVECTOR3						addMove;						//移動速度加算のため
	D3DXVECTOR3						aabbMin;						//AABBの初期値
	D3DXVECTOR3						aabbMax;						//AABBの初期値
	D3DXVECTOR3						aabbMinGet;						//AABBにプレイヤーの今の場所を足したところ
	D3DXVECTOR3						aabbMaxGet;						//AABBにプレイヤーの今の場所を足したところ
	std::unique_ptr<CSoundSource>	seJump;							//ジャンプSE
	float							radius;							//半径
	float							friction;						//摩擦
	float							deathCount;						//死亡までのカウント
	bool							playerStop = false;				//動けない状態
	float							diedTime = 0.0f;				//死亡する時間
	float							rate;							//モーフィング用時間
	float							currentAngleY;					//現在のアングル
	float							targetAngleY;					//ターゲットのアングル
};