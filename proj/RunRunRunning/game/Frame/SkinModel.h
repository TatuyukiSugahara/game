/*!
*@brief	スキンモデル
*/
#pragma once

#include "Animation.h"
#include "Texture.h"

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
			viewMatrix
			projMatrix
			isDrawToShadowMap
	*/
	void Render(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawToShadowMap);
	
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
	//影を受けるフラグセット
	void SetShadowReceiverFlag(const bool flag)
	{
		ShadowReceiverFlag = flag;
	}
	//影を描画するフラグセット
	void SetDrawToShadowMap(const bool flag)
	{
		isDrawToShadowMap = flag;
	}
	/*!
	*@brief 法線マップフラグを設定。
	*/
	void SetNormalMap(const bool flag)
	{
		isNormalMap = flag;
	}
	//すぺきゅらマップフラグをセット
	void SetSpecularMap(const bool flag)
	{
		isSpecularMap = flag;
	}
	//エフェクトをゲット
	ID3DXEffect* GetEffect() const
	{
		return pEffect;
	}
	//エフェクトをセットする
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	/*!
	* @brief	オリジナルメッシュを取得。
	*/
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;
	/*!
	* @brief	先頭のメッシュを取得。
	*/
	LPD3DXMESH GetOrgMeshFirst() const;

	//モーフィング処理の実行。
	//morphTargetA	モーフターゲット笑顔
	//morphTargetB　もーふターゲット真顔
	//rate モーフィングレート。
	void Morphing(SkinModel* morphTargetA, SkinModel* morphTargetB, float rate);

	/*!
	* @brief	ノーマルマップセット。
	*/
	void SetNormalMap(const LPDIRECT3DTEXTURE9& normal)
	{
		normalMap = normal;
	}
	/*!
	*@brief スペキュラマップを設定。
	*/
	void SetSpecularMap(const LPDIRECT3DTEXTURE9& specMap)
	{
		specularMap = specMap;
	}
	/*!
	*@brief フレネルを設定。
	*/
	void SetHureneruflg(const bool flag)
	{
		hureneruflg = flag;
	}
	/*!
	*@brief 地面かどうか設定。
	*/
	void SetGround(const bool flag)
	{
		Ground = flag;
	}
	//セットテクスチャ。
	void SetTexture(const char* tex,const bool isCube)
	{
		texture.Load(tex, isCube);
	}
	//セットスカイキューブ？
	void SetSkyCube(const bool flag)
	{
		SkyCube = flag;
	}
	//メッシュをツリー構造で調べて作成する
	void CreateMeshList(LPD3DXFRAME pFrame);
	//メッシュをゲット
	const LPD3DXMESH& GetMesh(const LPD3DXMESHCONTAINER& pMeshContainerBase) const;
	//メッシュリストをゲット
	const std::vector<LPD3DXMESH>& GetMeshList() const
	{
		return meshList;
	}

private:
	D3DXMATRIX			worldMatrix;				//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;				//!<回転行列。
	SkinModelData*		skinModelData;				//!<スキンモデルデータ。
	ID3DXEffect*		pEffect;					//!<エフェクト。
	Animation			animation;					//!<アニメーション。
	CLight*				light;						//!<ライト。
	bool				ShadowReceiverFlag;			//!<影を受ける？
	bool				isDrawToShadowMap;			//!<影を描画する？
	bool				isNormalMap;				//<!ノーマルマップフラグ
	bool				isSpecularMap;				//<!スペキュラマップフラグ
	bool				Ground;						//<!地面ですか？
	LPDIRECT3DTEXTURE9	normalMap;					//<!ノーマルマップ。
	LPDIRECT3DTEXTURE9  specularMap;				//<!スペキュラマップ。
	bool				hureneruflg = false;		//<!ふちを光らせる。
	CTexture			texture;					//テクスチャ
	bool				SkyCube = false;			//スカイキューブか?
	std::vector<LPD3DXMESH>			meshList;		//メッシュリスト
};
