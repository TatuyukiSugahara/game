#pragma once

//土管チップの配置情報。
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
* @brief	土管クラス。
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
	//配置情報のテーブルサイズゲット
	const int& GetSize() const
	{
		return tableSize;
	}
	//土管配置情報のテーブルサイズゲット
	const int& GetArraySize() const
	{
		return arraySize;
	}
	//土管に入っているかフラグ。
	const bool& GetIsPipe() const
	{
		return isPipe;
	}
	//土管の剛体ゲット
	const btRigidBody *GetPipe() const
	{
		return *rigidBodypipe;
	}
	//あたり判定作成
	void CreateCollision();	
	//あたり判定追加
	void AddRigidBody();	
	//あたり判定削除
	void RemoveRigidBody();	
private:
	
	static const int				MAXCOLLISION = 30;				//コリジョンの上限
	btCollisionShape*				pipeboxShape[MAXCOLLISION];		//地面のコリジョン形状。
	btRigidBody*					rigidBodypipe[MAXCOLLISION];	//剛体。
	btDefaultMotionState*			myMotionState;					//モーションステート
	bool							isAddCollision;					//コリジョン追加フラグ
	std::vector<CPipeChip*>			pipeChipList;					//土管チップのリスト。
	SPipeChipLocInfo*				pipeChipTable;					//土管コリジョン情報のテーブル
	SCollisionInfoPipe*				collisionTablpipe;				//土管配置情報のテーブル
	int								arraySize;						//土管配置情報のテーブルサイズ
	int								tableSize;						//配置情報のテーブルサイズ
	int								count;							//土管に入るカウント;
	D3DXVECTOR3						nextPos;						//次の土管の場所;
	bool							isPipe;							//土管に入るフラグ;
	std::unique_ptr<CSoundSource>	sePipe;
};
