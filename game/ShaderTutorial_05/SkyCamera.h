#pragma once

class CPlayer;

/*!
*@brief	カメラクラス。
*/
class CSkyCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<ビュー行列。カメラ行列
	D3DXMATRIX				projectionMatrix;	//!<プロジェクション行列。ビュー空間から射影空間に変換する行列。
	D3DXMATRIX				mRot;				//!<回転行列
	D3DXMATRIX				viewMatrixRotInv;			//回転行列の逆行列。
	D3DXVECTOR3				vEyePt;				//!<カメラの視点。
	D3DXVECTOR3				vLookatPt;			//!<カメラの注視点。
	D3DXVECTOR3				vUpVec;				//!<カメラの上方向。
	D3DXVECTOR3				toPos;				//!<視点から注視点のベクトル
	D3DXVECTOR3				cameradir;			//カメラの方向
	float					Far;				//!<遠平面。
	float					Near;				//!<近平面。
	float					aspect;				//!<アスペクト比
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CSkyCamera();
	/*!
	*@brief	デストラクタ
	*/
	~CSkyCamera();
	//アスペクト比を設定。
	void CSkyCamera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//アスペクト比を取得。
	float CSkyCamera::GetAspect()
	{
		return aspect;
	}
	//ファーを設定。
	void CSkyCamera::SetFar(float _far)
	{
		Far = _far;
	}
	//ニアーの取得。
	float CSkyCamera::GetNear()
	{
		return Near;
	}
	//ファーの取得。
	float CSkyCamera::GetFar()
	{
		return Far;
	}
	//ニアーを設定。
	void CSkyCamera::SetNear(float _near)
	{
		Near = _near;
	}
	//視点のセッター
	void CSkyCamera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//視点のゲッター
	D3DXVECTOR3 CSkyCamera::GetEyePt()
	{
		return vEyePt;
	}
	//注視点のセッター
	void CSkyCamera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//注視点のゲッター。
	D3DXVECTOR3 CSkyCamera::GetLookatPt()
	{
		return vLookatPt;
	}
	//上方向のセッター
	void CSkyCamera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//上方向のゲッター
	D3DXVECTOR3 CSkyCamera::GetUpVec()
	{
		return vUpVec;
	}
	//ビュー行列のセッター。
	void CSkyCamera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//ビュー行列のゲッター
	D3DXMATRIX CSkyCamera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//回転行列の逆行列ゲッター
	D3DXMATRIX CSkyCamera::GetViewMatrixInv()
	{
		return viewMatrixRotInv;
	}
	//プロジェクション行列のセッター
	void CSkyCamera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//プロジェクション行列のゲッター
	D3DXMATRIX CSkyCamera::GetProjectionMatrix()
	{
		return projectionMatrix;
	}
	//回転のゲッター
	D3DXMATRIX GetRot()
	{
		return mRot;
	}
	//============================================================
	//カメラが横に回転。
	//============================================================
	void RotTransversal(float roty);
	//============================================================
	//カメラが縦に回転。
	//============================================================
	void RotLongitudinal(float rotx);
	/*!
	*@brief	カメラの更新処理。
	*/
	D3DXVECTOR3 GetCSkyCameraDir()
	{
		return cameradir;
	}
	void Update();
	/*!
	*@brief	カメラの初期化。
	*/
	void Init();
};