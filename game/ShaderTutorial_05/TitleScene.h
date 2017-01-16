#pragma once 
#include "Title.h"
#include "TitleCamera.h"
#include "TitleLight.h"
#include "Scene\Scene.h"
#include "Fade.h"

class CTitleScene : public CScene
{
public:
	CTitleScene(){}
	~CTitleScene(){}
	void Init();
	void Update();
	void Render();
	HRESULT CreateSprite();	//スプライト生成関数

private:
	LPD3DXSPRITE m_pSprite;			//スプライト
	CTitle title;					//タイトル
	CTitleCamera camera;
	CTitleLight light;
	CFade fade;

	float Timer = 0.0f;
	const float NEXT = 5.0f;
	bool Fade = false;
};

extern CTitleScene g_titlescene;