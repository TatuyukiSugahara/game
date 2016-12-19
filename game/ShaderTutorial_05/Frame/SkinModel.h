/*!
*@brief	スキンモデル
*/
#pragma once

#include "Animation.h"


class SkinModelData;
class RenderContext;
class CLight;
/*!
*@brief	スキンモデル
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	初期化
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	描画。
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawToShadowMap);
	
	/*!
	*@brief	ワールド行列を更新。
	*@details
	* 後でCMotionクラスに移動させます。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );

	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		CLight* light,
		LPDIRECT3DTEXTURE9	normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		bool isDrawToShadowMap);

	void DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		CLight* light,
		LPDIRECT3DTEXTURE9	normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		bool isDrawToShadowMap
		);
	/*!
	*@brief	ライトを設定。
	*/
	void SetLight(CLight* light)
	{
		this->light = light;
	}
	void SetShadowReceiverFlag(bool flag)
	{
		ShadowReceiverFlag = flag;
	}
	void SetDrawToShadowMap(bool flag)
	{
		isDrawToShadowMap = flag;
	}
	/*!
	*@brief 法線マップフラグを設定。
	*/
	void SetNormalMap(bool flag)
	{
		isNormalMap = flag;
	}
	void SetSpecularMap(bool flag)
	{
		isSpecularMap = flag;
	}
	ID3DXEffect* GetEffect()
	{
		return pEffect;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	/*!
	* @brief	先頭のメッシュを取得。
	*/
	LPD3DXMESH GetOrgMeshFirst() const;
	/*!
	* @brief	ノーマルマップセット。
	*/
	void SetNormalMap(LPDIRECT3DTEXTURE9 normal)
	{
		normalMap = normal;
	}
	/*!
	*@brief スペキュラマップを設定。
	*/
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
private:
	D3DXMATRIX			worldMatrix;			//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;			//!<回転行列。
	SkinModelData*		skinModelData;			//!<スキンモデルデータ。
	ID3DXEffect*		pEffect;				//!<エフェクト。
	Animation			animation;				//!<アニメーション。
	CLight*				light;					//!<ライト。
	bool				ShadowReceiverFlag;
	bool				isDrawToShadowMap;
	bool				isNormalMap;			//<!ノーマルマップフラグ
	bool				isSpecularMap;		//<!スペキュラマップフラグ
	LPDIRECT3DTEXTURE9	normalMap;				//<!ノーマルマップ。
	LPDIRECT3DTEXTURE9  specularMap;				//<!スペキュラマップ。
};
