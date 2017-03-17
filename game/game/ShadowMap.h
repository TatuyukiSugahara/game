#pragma once

#include"RenderTarget.h"
#include "Frame\SkinModel.h"

extern LPDIRECT3DTEXTURE9 g_shadow;
extern LPDIRECT3DTEXTURE9 g_Unity;

class CShadowMap
{
public:
	//コンストラクタ
	CShadowMap(){
		pEffect = NULL;
	}
	//デストラクタ
	~CShadowMap(){
		Release();
	}
	//RenderTarget作成
	void Create(int w, int h);
	//ライト作成
	void CreateLight(D3DXMATRIX);
	//影描画
	void Render(D3DXMATRIX viewMatrix);
	//プレイヤー用影描画。
	void RenderUnity(D3DXMATRIX viewMatrix);
	//リリース
	void Release();
	//ライトビュープロジェゲット
	const D3DXMATRIX& Getlvpmatrix() const
	{
		return lVPMatrix;
	}
	//ライトの座標ゲット
	void SetLightPosition(const D3DXVECTOR3& pos)
	{
		lightPosition = pos;
	}
	//ライトの方向セット
	void SetLightDirection(const D3DXVECTOR3& Dir)
	{
		lightDirection = Dir;
	}
	//エフェクトセット
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	//エフェクトゲット
	const ID3DXEffect* GetEffect() const 
	{
		return pEffect;
	}
	/*!
	* @brief	近平面。
	*/
	const float& GetNear() const
	{
		return Near;
	}
	/*!
	* @brief	遠平面
	*/
	const float& GetFar() const
	{
		return Far;
	}
private:
	D3DVIEWPORT9		viewport;				//テクスチャのビューポート
	LPDIRECT3DSURFACE9	backBuffer;				//レンダーターゲットバックアップ
	LPDIRECT3DSURFACE9	backZ;					//デプスバッファバックアップ
	CRenderTarget		renderTarget;			//シャドーマップを書き込むレンダーターゲット
	CRenderTarget		renderTargetUnity;		//シャドーマップを書き込むプレイヤー用レンダーターゲット
	D3DXVECTOR3			lightPosition;			//ライトの座標
	D3DXVECTOR3			lightDirection;			//ライトの方向
	D3DXMATRIX			lvMatrix;				//ライトビューマトリクス
	D3DXMATRIX			lVPMatrix;				//ライトビュープロジェマトリクス
	D3DXMATRIX			projMatrix;				//プロジェ
	D3DXMATRIX			worldMatrix;			//ワールド
	ID3DXEffect*		pEffect;				//エフェクト
	float				Near;					//近平面。
	float				Far;					//遠平面。
	int					width;					//横
	int					height;					//縦
};