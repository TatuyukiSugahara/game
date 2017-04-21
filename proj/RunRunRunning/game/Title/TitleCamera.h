#pragma once

/*!
*@brief	�J�����N���X�B
*/
class CTitleCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXMATRIX				mRot;				//!<��]�s��
	D3DXVECTOR3				vEyePt;				//!<�J�����̎��_�B
	D3DXVECTOR3				vLookatPt;			//!<�J�����̒����_�B
	D3DXVECTOR3				vUpVec;				//!<�J�����̏�����B
	D3DXVECTOR3				toPos;				//!<���_���璍���_�̃x�N�g��
	D3DXVECTOR3				CTitleCameradir;			//�J�����̕���
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CTitleCamera();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~CTitleCamera();
	//�A�X�y�N�g���ݒ�B
	void CTitleCamera::SetAspect(float _aspect)
	{
		aspect = _aspect;
	}
	//�A�X�y�N�g����擾�B
	float CTitleCamera::GetAspect()
	{
		return aspect;
	}
	//�t�@�[��ݒ�B
	void CTitleCamera::SetFar(float _far)
	{
		Far = _far;
	}
	//�j�A�[�̎擾�B
	float CTitleCamera::GetNear()
	{
		return Near;
	}
	//�t�@�[�̎擾�B
	float CTitleCamera::GetFar()
	{
		return Far;
	}
	//�j�A�[��ݒ�B
	void CTitleCamera::SetNear(float _near)
	{
		Near = _near;
	}
	//���_�̃Z�b�^�[
	void CTitleCamera::SetEyePt(D3DXVECTOR3 pt)
	{
		vEyePt = pt;
	}
	//���_�̃Q�b�^�[
	D3DXVECTOR3 CTitleCamera::GetEyePt()
	{
		return vEyePt;
	}
	//�����_�̃Z�b�^�[
	void CTitleCamera::SetLookatPt(D3DXVECTOR3 pt)
	{
		vLookatPt = pt;
	}
	//�����_�̃Q�b�^�[�B
	D3DXVECTOR3 CTitleCamera::GetLookatPt()
	{
		return vLookatPt;
	}
	//������̃Z�b�^�[
	void CTitleCamera::SetUpVec(D3DXVECTOR3 up)
	{
		vUpVec = up;
	}
	//������̃Q�b�^�[
	D3DXVECTOR3 CTitleCamera::GetUpVec()
	{
		return vUpVec;
	}
	//�r���[�s��̃Z�b�^�[�B
	void CTitleCamera::SetViewMatrix(D3DXMATRIX mView)
	{
		viewMatrix = mView;
	}
	//�r���[�s��̃Q�b�^�[
	D3DXMATRIX CTitleCamera::GetViewMatrix()
	{
		return viewMatrix;
	}
	//�v���W�F�N�V�����s��̃Z�b�^�[
	void CTitleCamera::SetProjectionMatrix(D3DXMATRIX mProj)
	{
		projectionMatrix = mProj;
	}
	//�v���W�F�N�V�����s��̃Q�b�^�[
	D3DXMATRIX CTitleCamera::GetProjectionMatrix()
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