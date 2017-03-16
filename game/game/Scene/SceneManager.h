#pragma once

#include "Scene.h"

class CScene;

using namespace std;

class CSceneManager
{
public:
	//�X�e�[�W�̔ԍ�
	enum class StageNumber
	{
		Stage1 = 1,	//�X�e�[�W�P	
		Stage2,		//�X�e�[�W�Q
		StageBoss,	//�X�e�[�W�R(�{�X)
	};
	//�Q�[���̃V�[��
	enum class GameScene
	{
		Title,		//�^�C�g�����
		Game,		//�Q�[�����
		Result,		//���U���g���
	};
	CSceneManager();
	~CSceneManager();
	void InitializeScene();
	void UpdateScene();
	void RenderScene();
	void ChangeScene(const int& key);
	//���U���g�ɍs�����̃t���O�Z�b�g
	void SetResult(bool flag)
	{
		resultflag = flag;
	}
	//���U���g�ɂ������̃t���O���Q�b�g
	bool GetResult()
	{
		return resultflag;
	}
	//�R�C���̐����Q�b�g
	int GetNum()
	{
		return num;
	}
	//�R�C���̐��𑫂�
	void AddNum()
	{
		num++;
	}
	//�X�e�[�W�̔ԍ����Q�b�g
	StageNumber GetNumber()
	{
		return Number;
	}
	//�X�e�[�W�̔ԍ��Z�b�g
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
	bool resultflag = 0;		//0�̓S�[���A1�̓f�X
	int num = 0;				//�R�C���̐�
	StageNumber Number;
};