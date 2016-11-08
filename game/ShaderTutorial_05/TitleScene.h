#pragma once 
#include "Title.h"
#include "TitleCamera.h"
#include "TitleLight.h"

class CTitleScene
{
public:
	CTitleScene(){}
	~CTitleScene(){}
	void Init();
	void Update();
	void Render();
	HRESULT CreateSprite();	//�X�v���C�g�����֐�

private:
	LPD3DXSPRITE m_pSprite;			//�X�v���C�g
	CTitle title;					//�^�C�g��
	CTitleCamera camera;
	CTitleLight light;
};

extern CTitleScene g_titlescene;