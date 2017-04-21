#pragma once

/*!
*@brief	�J�����N���X�B
*/
class CResultCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXMATRIX				mRot;				//!<��]�s��
	D3DXVECTOR3				vEyePt;				//!<�J�����̎��_�B
	D3DXVECTOR3				vLookatPt;			//!<�J�����̒����_�B
	D3DXVECTOR3				vUpVec;				//!<�J�����̏�����B
	D3DXVECTOR3				toPos;				//!<���_���璍���_�̃x�N�g��
	D3DXVECTOR3				CResultCameradir;			//�J�����̕���
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CResultCamera();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~CResultCamera();
	//�A�X�y�N�g���ݒ�B
	void CResultCamera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//�A�X�y�N�g����擾�B
	float CResultCamera::GetAspect()
	{
		return aspect;
	}
	//�t�@�[��ݒ�B
	void CResultCamera::SetFar(float _far)
	{
		Far = _far;
	}
	//�j�A�[�̎擾�B
	float CResultCamera::GetNear()
	{
		return Near;
	}
	//�t�@�[�̎擾�B
	float CResultCamera::GetFar()
	{
		return Far;
	}
	//�j�A�[��ݒ�B
	void CResultCamera::SetNear(float _near)
	{
		Near = _near;
	}
	//���_�̃Z�b�^�[
	void CResultCamera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//���_�̃Q�b�^�[
	D3DXVECTOR3 CResultCamera::GetEyePt()
	{
		return vEyePt;
	}
	//�����_�̃Z�b�^�[
	void CResultCamera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//�����_�̃Q�b�^�[�B
	D3DXVECTOR3 CResultCamera::GetLookatPt()
	{
		return vLookatPt;
	}
	//������̃Z�b�^�[
	void CResultCamera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//������̃Q�b�^�[
	D3DXVECTOR3 CResultCamera::GetUpVec()
	{
		return vUpVec;
	}
	//�r���[�s��̃Z�b�^�[�B
	void CResultCamera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//�r���[�s��̃Q�b�^�[
	D3DXMATRIX CResultCamera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//�v���W�F�N�V�����s��̃Z�b�^�[
	void CResultCamera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//�v���W�F�N�V�����s��̃Q�b�^�[
	D3DXMATRIX CResultCamera::GetProjectionMatrix()
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
	void Init();
};