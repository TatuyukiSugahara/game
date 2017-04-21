#pragma once

#include "Scene.h"

class CScene;

using namespace std;

class CSceneManager
{
public:
	//ステージの番号
	enum class StageNumber
	{
		Stage1 = 1,	//ステージ１	
		Stage2,		//ステージ２
		StageBoss,	//ステージ３(ボス)
	};
	//ゲームのシーン
	enum class GameScene
	{
		Title,		//タイトル画面
		Game,		//ゲーム画面
		Result,		//リザルト画面
	};
	CSceneManager();
	~CSceneManager();
	void InitializeScene();
	void UpdateScene();
	void RenderScene();
	void ChangeScene(const int& key);
	//リザルトに行くかのフラグセット
	void SetResult(bool flag)
	{
		resultflag = flag;
	}
	//リザルトにいくかのフラグをゲット
	bool GetResult()
	{
		return resultflag;
	}
	//コインの数をゲット
	int GetNum()
	{
		return num;
	}
	//コインの数を足す
	void AddNum()
	{
		num++;
	}
	//ステージの番号をゲット
	StageNumber GetNumber()
	{
		return Number;
	}
	//ステージの番号セット
	//g_scenemanager->SetNumber(CSceneManager::StageNumber::Stage1);
	void SetNumber(int i)
	{
		Number = StageNumber(i);
	}
	CScene* GetScenes()
	{
		m_scenes;
	}
private:
	CScene* m_scenes;
	int nextScene = -1;
	bool resultflag = 0;		//0はゴール、1はデス
	int num = 0;				//コインの数
	StageNumber Number;
};