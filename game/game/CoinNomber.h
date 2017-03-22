#pragma once 
#include "Frame\2DImage.h"

class CCoinNomber : public C2DImage
{
public:
	CCoinNomber();
	~CCoinNomber();
	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Render(LPD3DXSPRITE)override;
	//桁ごとに描画するため
	void Render(const LPD3DXSPRITE, const int num, const D3DXVECTOR2 pos);
	//座標セット
	void SetPos(const D3DXVECTOR2& pos)
	{
		position = pos;
	}
	//1桁目の座標セット
	void Set1keta(const D3DXVECTOR2& keta)
	{
		keta1 = keta;
	}
	//2桁面の座標セット
	void Set2keta(const D3DXVECTOR2& keta)
	{
		keta2 = keta;
	}
	//3桁目の座標セット
	void Set3keta(const D3DXVECTOR2& keta)
	{
		keta3 = keta;
	}
	//カラーセット
	void SetColor(const int& r,const int& g, const int& b)
	{
		backColor = D3DCOLOR_ARGB(255, r, g, b);
	}
private:
	const int	NUMBER_NUM = 10;	//0から9のため10
	D3DXVECTOR2 keta1;				//1桁目
	D3DXVECTOR2 keta2;				//2桁目
	D3DXVECTOR2 keta3;				//3桁目
};