#pragma once

//マップチップの配置情報。
struct SPipeChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//大きさ	
};

//オブジェクトの詳細
struct SCollisionInfoPipe {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

#define MAXCOLLISION 30

class CPipeChip;

/*!
* @brief	マップクラス。
*/
class CPipe {
public:

	CPipe();
	~CPipe();
	void Init();
	void Update();
	//描画。
	void Render(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//土管移動
	void PipeMove(int now, int next, int pipenum);
	int GetSize()
	{
		return tableSize;
	}
	int GetArraySize()
	{
		return arraySize;
	}
	//土管に入っているかフラグ。
	bool GetIsPipe()
	{
		return isPipe;
	}
	btRigidBody *Get2DPipe()
	{
		return *m_rigidBody2Dpipe;
	}
	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody(int arraySize);		//2Dあたり判定追加
	void Remove2DRigidBody(int arraySize);	//2Dあたり判定削除
private:
	std::vector<CPipeChip*> pipeChipList;	//マップチップのリスト。
	int tableSize;
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_pipeboxShape[MAXCOLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dpipe[MAXCOLLISION];	//剛体3D。
	btRigidBody*		m_rigidBody2Dpipe[MAXCOLLISION];	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
	SPipeChipLocInfo* pipeChipTable;
	SCollisionInfoPipe* collisionTablpipe;

	int arraySize;
	int count;								//土管に入るカウント;
	D3DXVECTOR3			nextPos;			//次の土管の場所;
	bool				isPipe;				//土管に入るフラグ;

	CSoundSource* SEPipe;
};
