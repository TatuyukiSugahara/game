#pragma once 
#include "Frame\2DImage.h"

class CBossKatto : public C2DImage
{
public:
	CBossKatto();
	~CBossKatto();
	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Render(LPD3DXSPRITE pSprite)override;
	//座標セット
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	//カラーセット
	void SetColor(const int& r, const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}	
	//カットイン出すかフラグ
	void SetKatto(const bool& flag)
	{
		kattoFlag = flag;
	}
private:
	bool							kattoFlag;			//カットイン出すかフラグ
	bool							flag = false;		//SEならすふらぐ。
	std::unique_ptr<CSoundSource>	seKatto;			//カットインSE
};