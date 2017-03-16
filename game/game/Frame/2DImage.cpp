//テクスチャの読み込み・画像表示

#include "..\stdafx.h"
#include "2DImage.h"


C2DImage::C2DImage()
{
}


C2DImage::~C2DImage()
{
}

void C2DImage::Init()
{
	D3DXCreateTextureFromFileEx(g_pd3dDevice, this->texFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imgInfo, NULL, &this->pTexture);	//テクスチャ読込
	this->texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);	//テクスチャの中点セット
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//描画領域
	memcpy(&this->rect, &rec, sizeof(RECT));					//描画領域セット
}

void C2DImage::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//スプライト描画開始
	pSprite->SetTransform(&this->transformMatrix);	//変換行列セット
	pSprite->Draw(this->pTexture, &this->rect, &D3DXVECTOR3(this->texCenter.x, this->texCenter.y, 0.0f), NULL, this->backColor);	//スプライトにテクスチャ貼付け
	pSprite->End();	//スプライト描画終了
}

void C2DImage::SetupMatrices()
{
	D3DXMatrixIdentity(&this->transformMatrix);	//ワールド行列初期化
	D3DXMatrixTransformation2D(&this->transformMatrix, NULL, 0.0f, &this->scale, NULL, D3DXToRadian(this->angle), &this->position);	//変換行列作成
}