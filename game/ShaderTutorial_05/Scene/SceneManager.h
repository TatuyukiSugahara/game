#pragma once

#include <vector>
#include "Scene.h"

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
private:
	CScene* m_scenes;
	int nextScene = -1;
	bool resultflag = 0;		//0�̓S�[���A1�̓f�X
};