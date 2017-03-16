#pragma once

class CPlayer;

/*!
 *@brief	カメラクラス。
 */
class Camera {
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
	float					bosstime;			//!<ボス登場時のカメラ演出の時間
	float					Angle;				//!<画角
	float					camerahokan = 1.0f;	//!<カメラの線形保管。
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	Camera();
	/*!
	 *@brief	デストラクタ
	 */
	~Camera();
	//アスペクト比を設定。
	void SetAspect(const float& _aspect)
	{
		aspect = _aspect;
	}
	//アスペクト比を取得。
	const float& GetAspect() const
	{
		return aspect;
	}
	//ファーを設定。
	void SetFar(const float& _far)
	{
		Far = _far;
	}
	//ニアーの取得。
	const float& GetNear() const
	{
		return Near;
	}
	//ファーの取得。
	const float& GetFar() const
	{
		return Far;
	}
	//ニアーを設定。
	void SetNear(const float& _near)
	{
		Near = _near;
	}
	//視点のセッター
	void SetEyePt(const D3DXVECTOR3& pt)
	{
		vEyePt = pt;
	}
	//視点のゲッター
	const D3DXVECTOR3& GetEyePt() const
	{
		return vEyePt;
	}
	//注視点のセッター
	void SetLookatPt(const D3DXVECTOR3& pt)
	{
		vLookatPt = pt;
	}
	//注視点のゲッター。
	const D3DXVECTOR3& GetLookatPt() const
	{
		return vLookatPt;
	}
	//上方向のセッター
	void SetUpVec(const D3DXVECTOR3& up)
	{
		vUpVec = up;
	}
	//上方向のゲッター
	const D3DXVECTOR3& GetUpVec() const
	{
		return vUpVec;
	}
	//ビュー行列のセッター。
	void SetViewMatrix(const D3DXMATRIX& mView)
	{
		viewMatrix = mView;
	}
	//ビュー行列のゲッター
	const D3DXMATRIX& GetViewMatrix() const
	{
		return viewMatrix;
	}
	//回転行列の逆行列ゲッター
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return viewMatrixRotInv;
	}
	//プロジェクション行列のセッター
	void SetProjectionMatrix(const D3DXMATRIX& mProj)
	{
		projectionMatrix = mProj;
	}
	//プロジェクション行列のゲッター
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return projectionMatrix;
	}
	//回転のゲッター
	const D3DXMATRIX& GetRot() const
	{
		return mRot;
	}
	/*!
	*@brief	カメラの方向ゲット。
	*/
	const D3DXVECTOR3& GetCameraDir()
	{
		return cameradir;
	}
	//カメラが横に回転。
	void RotTransversal(float roty);
	//カメラが縦に回転。
	void RotLongitudinal(float rotx);
	//ボスカメラ
	void BossCamera();
	/*!
	*@brief	カメラの更新。
	*/
	void Update();
	/*!
	 *@brief	カメラの初期化。
	 */
	void Init();
};