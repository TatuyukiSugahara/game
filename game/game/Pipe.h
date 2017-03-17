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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//土管に入った時の処理。
	void InPipe();
	//土管移動
	void PipeMove(int now, int next, int pipenum);
	const int& GetSize() const
	{
		return tableSize;
	}
	const int& GetArraySize() const
	{
		return arraySize;
	}
	//土管に入っているかフラグ。
	const bool& GetIsPipe() const
	{
		return isPipe;
	}
	const btRigidBody *GetPipe() const
	{
		return *rigidBodypipe;
	}
	void CreateCollision();				//あたり判定
	void AddRigidBody(int arraySize);		//あたり判定追加
	void RemoveRigidBody(int arraySize);	//あたり判定削除
private:
	
	static const int				MAXCOLLISION = 30;				//コリジョンの上限
	btCollisionShape*				pipeboxShape[MAXCOLLISION];		//地面のコリジョン形状。
	btRigidBody*					rigidBodypipe[MAXCOLLISION];	//剛体。
	btDefaultMotionState*			myMotionState;					//モーションステート
	bool							isAddCollision;
	SPipeChipLocInfo*				pipeChipTable;
	std::vector<CPipeChip*>			pipeChipList;					//マップチップのリスト。
	int								tableSize;
	SCollisionInfoPipe*				collisionTablpipe;
	int								arraySize;
	int								count;							//土管に入るカウント;
	D3DXVECTOR3						nextPos;						//次の土管の場所;
	bool							isPipe;							//土管に入るフラグ;
	std::unique_ptr<CSoundSource>	sePipe;
};
