#pragma once
/*!
*@brief	レンダリングターゲット。
*/
class CRenderTarget {
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CRenderTarget();
	/*!
	*@brief	デストラクタ。
	*/
	~CRenderTarget();
	/*!
	*@brief	解放。
	*/
	void Release();
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
	void Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality);
	/*!
	*@brief	レンダリングターゲットを取得。
	*/
	const LPDIRECT3DSURFACE9& GetRenderTarget() const
	{
		return m_surface;
	}
	/*!
	*@brief	デプスステンシルバッファを取得。
	*/
	const LPDIRECT3DSURFACE9& GetDepthStencilBuffer() const
	{
		return m_depthSurface;
	}
	/*!
	*@brief	テクスチャを取得。
	*/
	const LPDIRECT3DTEXTURE9& GetTexture() const
	{
		return m_texture;
	}
	/*!
	*@brief	幅を取得。
	*/
	const int& GetWidth() const
	{
		return m_width;
	}
	/*!
	*@brief	高さを取得。
	*/
	const int& GetHeight() const
	{
		return m_height;
	}
private:
	LPDIRECT3DSURFACE9		m_depthSurface;		//!<深度バッファ用のサーフェイス
	LPDIRECT3DTEXTURE9		m_texture;			//!<書き込み先のテクスチャ。
	LPDIRECT3DSURFACE9		m_surface;			//!<サーフェイス
	int						m_width = 0;		//!<幅
	int						m_height = 0;		//!<高さ
};