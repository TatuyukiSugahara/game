#include "stdafx.h"
#include "RenderTarget.h"
/*!
*@brief	レンダリングターゲット。
*/
	/*!
	*@brief	コンストラクタ。
	*/
CRenderTarget::CRenderTarget()
{
	depthSurface = NULL;
	texture = NULL;
	surface = NULL;
	texture = NULL;
}
	/*!
	*@brief	デストラクタ。
	*/
CRenderTarget::~CRenderTarget()
{
	Release();
}
	/*!
	*@brief	解放。
	*/
void CRenderTarget::Release()
{
	if (texture != nullptr) {
		texture->Release();
		texture = NULL;
	}
	if (depthSurface != nullptr) {
		depthSurface->Release();
		depthSurface = NULL;
	}
	if (surface != NULL) {
		surface->Release();
		surface = NULL;
	}
}
	/*!
	*@brief	レンダリングターゲットの作成。
	*@param[in]	w					レンダリングターゲットの幅。
	*@param[in]	h					レンダリングターゲットの高さ。
	*@param[in]	mipLevel			ミップマップレベル。
	*@param[in]	colorFormat			カラーバッファのフォーマット。
	*@param[in]	depthStencilFormat	デプスステンシルバッファのフォーマット。
	*@param[in]	multiSampleType		マルチサンプリングの種類。
	*@param[in]	multiSampleQuality	マルチサンプリングの品質。
	*/
void CRenderTarget::Create(
	int w,
	int h,
	int mipLevel,
	D3DFORMAT colorFormat,
	D3DFORMAT depthStencilFormat,
	D3DMULTISAMPLE_TYPE multiSampleType,
	int multiSampleQuality)
{
	//デプスステンシルバッファの作成。
	HRESULT hr = g_pd3dDevice->CreateDepthStencilSurface(
		w,
		h,
		static_cast<D3DFORMAT>(depthStencilFormat),
		static_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),
		multiSampleQuality,
		TRUE,
		&depthSurface,
		NULL
		);
	//カラーバッファを作成。
	hr = g_pd3dDevice->CreateTexture(
		w,
		h,
		mipLevel,
		D3DUSAGE_RENDERTARGET,
		static_cast<D3DFORMAT>(colorFormat),
		D3DPOOL_DEFAULT,
		&texture,
		NULL
		);
	texture->GetSurfaceLevel(0, &surface);

	width = w;
	height = h;
}