#pragma once 
#include "Frame\2DImage.h"

class CBossClear : public C2DImage
{
public:
	CBossClear();
	~CBossClear();
	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Render(LPD3DXSPRITE)override;
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
	//クリアフラグセット
	void SetClear(const bool& flag)
	{
		Clear = flag;
	}
private:
	bool							Clear;				//クリアしたかのフラグ
	bool							flag = false;		//SE鳴らすフラグ。
	std::unique_ptr<CSoundSource>	seGoal;				//クリアSE
};