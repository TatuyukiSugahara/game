#pragma once 
#include "Title.h"
#include "TitleCamera.h"
#include "TitleLight.h"
#include "Scene\Scene.h"
#include "Fade.h"
#include "TitleStart.h"
#include "TitleStartBG.h"
#include "Sound\SoundSource.h"


class CTitleScene : public CScene
{
public:
	CTitleScene(){}
	~CTitleScene();
	void Init();
	void Update();
	void Render();
	HRESULT CreateSprite();	//�X�v���C�g�����֐�

private:
	LPD3DXSPRITE m_pSprite;			//�X�v���C�g
	CTitle title;					//�^�C�g��
	CTitleCamera camera;
	CTitleLight light;
	CFade fade;
	CTitleStart titlestart;
	CTitleStartBG titlestartBG;
	CSoundSource* SETitle;
};

extern CTitleScene g_titlescene;