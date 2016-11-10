#pragma once

/*!
*@brief	カメラクラス。
*/
class CResultCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<ビュー行列。カメラ行列
	D3DXMATRIX				projectionMatrix;	//!<プロジェクション行列。ビュー空間から射影空間に変換する行列。
	D3DXMATRIX				mRot;				//!<回転行列
	D3DXVECTOR3				vEyePt;				//!<カメラの視点。
	D3DXVECTOR3				vLookatPt;			//!<カメラの注視点。
	D3DXVECTOR3				vUpVec;				//!<カメラの上方向。
	D3DXVECTOR3				toPos;				//!<視点から注視点のベクトル
	D3DXVECTOR3				CResultCameradir;			//カメラの方向
	float					Far;				//!<遠平面。
	float					Near;				//!<近平面。
	float					aspect;				//!<アスペクト比
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CResultCamera();
	/*!
	*@brief	デストラクタ
	*/
	~CResultCamera();
	//アスペクト比を設定。
	void CResultCamera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//アスペクト比を取得。
	float CResultCamera::GetAspect()
	{
		return aspect;
	}
	//ファーを設定。
	void CResultCamera::SetFar(float _far)
	{
		Far = _far;
	}
	//ニアーの取得。
	float CResultCamera::GetNear()
	{
		return Near;
	}
	//ファーの取得。
	float CResultCamera::GetFar()
	{
		return Far;
	}
	//ニアーを設定。
	void CResultCamera::SetNear(float _near)
	{
		Near = _near;
	}
	//視点のセッター
	void CResultCamera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//視点のゲッター
	D3DXVECTOR3 CResultCamera::GetEyePt()
	{
		return vEyePt;
	}
	//注視点のセッター
	void CResultCamera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//注視点のゲッター。
	D3DXVECTOR3 CResultCamera::GetLookatPt()
	{
		return vLookatPt;
	}
	//上方向のセッター
	void CResultCamera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//上方向のゲッター
	D3DXVECTOR3 CResultCamera::GetUpVec()
	{
		return vUpVec;
	}
	//ビュー行列のセッター。
	void CResultCamera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//ビュー行列のゲッター
	D3DXMATRIX CResultCamera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//プロジェクション行列のセッター
	void CResultCamera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//プロジェクション行列のゲッター
	D3DXMATRIX CResultCamera::GetProjectionMatrix()
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