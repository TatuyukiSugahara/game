#pragma once

class CPlayer;

/*!
 *@brief	�J�����N���X�B
 */
class Camera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXVECTOR3				vEyePt;				//!<�J�����̎��_�B
	D3DXVECTOR3				vLookatPt;			//!<�J�����̒����_�B
	D3DXVECTOR3				vUpVec;				//!<�J�����̏�����B
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
	CPlayer* player;
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Camera();
	/*!
	 *@brief	�f�X�g���N�^
	 */
	~Camera();
	//�A�X�y�N�g���ݒ�B
	void Camera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//�A�X�y�N�g����擾�B
	float Camera::GetAspect()
	{
		return aspect;
	}
	//�t�@�[��ݒ�B
	void Camera::SetFar(float _far)
	{
		Far = _far;
	}
	//�j�A�[�̎擾�B
	float Camera::GetNear()
	{
		return Near;
	}
	//�t�@�[�̎擾�B
	float Camera::GetFar()
	{
		return Far;
	}
	//�j�A�[��ݒ�B
	void Camera::SetNear(float _near)
	{
		Near = _near;
	}
	//���_�̃Z�b�^�[
	void Camera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//���_�̃Q�b�^�[
	D3DXVECTOR3 Camera::GetEyePt()
	{
		return vEyePt;
	}
	//�����_�̃Z�b�^�[
	void Camera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//�����_�̃Q�b�^�[�B
	D3DXVECTOR3 Camera::GetLookatPt()
	{
		return vLookatPt;
	}
	//������̃Z�b�^�[
	void Camera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//������̃Q�b�^�[
	D3DXVECTOR3 Camera::GetUpVec()
	{
		return vUpVec;
	}
	//�r���[�s��̃Z�b�^�[�B
	void Camera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//�r���[�s��̃Q�b�^�[
	D3DXMATRIX Camera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//�v���W�F�N�V�����s��̃Z�b�^�[
	void Camera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//�v���W�F�N�V�����s��̃Q�b�^�[
	D3DXMATRIX Camera::GetProjectionMatrix()
	{
		return projectionMatrix;
	}
	/*!
	 *@brief	�J�����̍X�V�����B
	 */
	void Update();
	/*!
	 *@brief	�J�����̏������B
	 */
	void Init(CPlayer* player);
};