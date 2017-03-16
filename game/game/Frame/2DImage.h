#pragma once

class C2DImage
{
public:
	C2DImage();
	virtual ~C2DImage();
	virtual void Init();
	virtual void Update() = 0;
	virtual void Render(LPD3DXSPRITE);
	void SetupMatrices();
protected:
	D3DXVECTOR2 position;			//位置情報
	float angle;					//回転情報
	D3DXVECTOR2 scale;			//スケール情報
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャ
	D3DCOLOR backColor;			//背景カラー
	LPCTSTR texFileName;			//テクスチャファイル名
	D3DXVECTOR2 texCenter;		//テクスチャの中点
	RECT rect;					//描画矩形
	D3DXMATRIX transformMatrix;	//変換行列
	D3DXIMAGE_INFO imgInfo;			//テクスチャ情報
};

