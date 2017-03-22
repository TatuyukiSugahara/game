#pragma once 
#include "Frame\2DImage.h"

class CBossName : public C2DImage
{
public:
	CBossName();
	~CBossName();
	//初期化
	void Init()override;
	//更新
	void Update()override;
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
	//描画するかフラグセット
	void SetRender(const bool& flag)
	{
		renderFlag = flag;
	}
private:
	bool renderFlag = false;	//描画するかのフラグ
};