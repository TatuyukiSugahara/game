#pragma once

/*!
*@brief	カメラクラス。
*/
class CTitleCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<ビュー行列。カメラ行列
	D3DXMATRIX				projectionMatrix;	//!<プロジェクション行列。ビュー空間から射影空間に変換する行列。
	D3DXMATRIX				mRot;				//!<回転行列
	D3DXVECTOR3				vEyePt;				//!<カメラの視点。
	D3DXVECTOR3				vLookatPt;			//!<カメラの注視点。
	D3DXVECTOR3				vUpVec;				//!<カメラの上方向。
	D3DXVECTOR3				toPos;				//!<視点から注視点のベクトル
	D3DXVECTOR3				CTitleCameradir;			//カメラの方向
	float					Far;				//!<遠平面。
	float					Near;				//!<近平面。
	float					aspect;				//!<アスペクト比
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CTitleCamera();
	/*!
	*@brief	デストラクタ
	*/
	~CTitleCamera();
	//アスペクト比を設定。
	void CTitleCamera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//アスペクト比を取得。
	float CTitleCamera::GetAspect()
	{
		return aspect;
	}
	//ファーを設定。
	void CTitleCamera::SetFar(float _far)
	{
		Far = _far;
	}
	//ニアーの取得。
	float CTitleCamera::GetNear()
	{
		return Near;
	}
	//ファーの取得。
	float CTitleCamera::GetFar()
	{
		return Far;
	}
	//ニアーを設定。
	void CTitleCamera::SetNear(float _near)
	{
		Near = _near;
	}
	//視点のセッター
	void CTitleCamera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//視点のゲッター
	D3DXVECTOR3 CTitleCamera::GetEyePt()
	{
		return vEyePt;
	}
	//注視点のセッター
	void CTitleCamera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//注視点のゲッター。
	D3DXVECTOR3 CTitleCamera::GetLookatPt()
	{
		return vLookatPt;
	}
	//上方向のセッター
	void CTitleCamera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//上方向のゲッター
	D3DXVECTOR3 CTitleCamera::GetUpVec()
	{
		return vUpVec;
	}
	//ビュー行列のセッター。
	void CTitleCamera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//ビュー行列のゲッター
	D3DXMATRIX CTitleCamera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//プロジェクション行列のセッター
	void CTitleCamera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//プロジェクション行列のゲッター
	D3DXMATRIX CTitleCamera::GetProjectionMatrix()
	{
		return projectionMatrix;
	}
	/*!
	*@brief	カメラの更新処理。
	*/
	void Update();
	/*!
	*@brief	カメラの初期化。
	*/
	void Init();
};