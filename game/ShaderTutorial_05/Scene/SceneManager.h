#pragma once

#include "Scene.h"

enum StageNomber
{
	Stage1 = 1,
	Stage2,
	StageBoss,
};

class CScene;

using namespace std;

class CSceneManager
{
public:
	CSceneManager();
	void InitializeScene();
	void UpdateScene();
	void RenderScene();
	void ChangeScene(const int& key);
	void SetResult(bool flag)
	{
		resultflag = flag;
	}
	bool GetResult()
	{
		return resultflag;
	}
	int GetNum()
	{
		return num;
	}
	void AddNum()
	{
		num++;
	}
	StageNomber GetNomber()
	{
		return Nomber;
	}
	void SetNonber(int i)
	{
		Nomber = StageNomber(i);
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
	StageNomber Nomber;
};