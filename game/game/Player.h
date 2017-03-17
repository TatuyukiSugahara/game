#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"
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
		return movespeed;
	}
	//プレイヤーのAABBのMAXをゲット
	const D3DXVECTOR3& GetAABBMax() const
	{
		return aabbMaxget;
	}
	//プレイヤーのAABBのMINをゲット
	const D3DXVECTOR3& GetAABBMin() const
	{
		return aabbMinget;
	}
	const D3DXMATRIX& GetRot() const
	{
		return mRotation;
	}
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		skinmodel.SetEffect(effect);
	}
	const ID3DXEffect* GetEffect() const
	{
		return skinmodel.GetEffect();
	}
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		movespeed = speed;
	}
	const Life& GetLifeState() const
	{
		return lifestate;
	}
	void SetLifeState(const Life& life)
	{
		lifestate = life;
	}
	void SetScale(const D3DXVECTOR3& scal)
	{
		scale = scal;
	}
	const D3DXVECTOR3& GetScale() const
	{
		return scale;
	}
	void SubScale(const D3DXVECTOR3& sub)
	{
		scale -= sub;
	}
	void AddScale(const D3DXVECTOR3& add)
	{
		scale += add;
	}
	void SetState(const PlayerState& state)
	{
		this->state = state;
	}
	void SetPlyaerStop(const bool& stop)
	{
		playerstop = stop;
	}
	const bool& GetPlayerStop() const
	{
		return playerstop;
	}
	void SetDiedTime(const float& time)
	{
		diedTime = time;
	}
	void Move(float maxmove);
	void Jump();
	void State();
	void Died();		//死亡
	void Clear();		//クリア時
private:
	D3DXVECTOR3						position;						//座標。
	D3DXVECTOR3						movespeed;						//移動速度
	D3DXVECTOR3						scale;							//スケールw
	D3DXMATRIX						mRotation;						//回転行列。
	SkinModel						skinmodel;						//オリジナル
	SkinModel						skinmodelA;						//モーフィング用A
	SkinModel						skinmodelB;						//モーフィング用B
	SkinModelData					modelData;						//オリジナル
	SkinModelData					modelDataA;						//モーフィング用A
	SkinModelData					modelDataB;						//モーフィング用B
	Animation 						animation;						//アニメーション
	CLight							light;							//ライト
	LPDIRECT3DTEXTURE9				normalMap = NULL;				//ノーマルマップ
	LPDIRECT3DTEXTURE9				specularMap = NULL;				//スペキュラマップ。
	CTurn							turn;							//ターンクラス
	CCharacterController			characterController;			//キャラクターコントローラー
	PlayerState						state;							//プレイヤーの状態
	Life							lifestate;						//プレイヤー生死
	D3DXQUATERNION					rotation;						//回転クォータニオン
	D3DXVECTOR3						addmove;						//次の移動
	D3DXVECTOR3						aabbMin;						//AABBの初期値
	D3DXVECTOR3						aabbMax;						//AABBの初期値
	D3DXVECTOR3						aabbMinget;						//AABBにプレイヤーの今の場所を足したところ
	D3DXVECTOR3						aabbMaxget;						//AABBにプレイヤーの今の場所を足したところ
	std::unique_ptr<CSoundSource>	SEjump;							//ジャンプSE
	float							radius;							//半径
	float							friction;						//摩擦
	float							deathCount;						//死亡までのカウント
	bool							playerstop = false;				//動けない状態
	float							diedTime = 0.0f;				//死亡する時間
	float							rate;							//モーフィング用時間
	float							currentAngleY;					//現在のアングル
	float							targetAngleY;					//ターゲットのアングル

	

};