#pragma once

#include "Scene.h"

enum StageNomber
{
	Stage1,
	Stage2,
};

class CScene;

using namespace std;

class CSceneManager
{
public:
	CSceneManager()
	{
		m_scenes = NULL;
	}
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
private:
	CScene* m_scenes;
	int nextScene = -1;
	bool resultflag = 0;		//0はゴール、1はデス
	int num = 0;
};