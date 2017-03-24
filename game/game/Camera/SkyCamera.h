#pragma once

class CPlayer;

/*!
*@brief	�J�����N���X�B
*/
class CSkyCamera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXMATRIX				rot;				//!<��]�s��
	D3DXMATRIX				viewMatrixRotInv;	//!<��]�s��̋t�s��B
	D3DXVECTOR3				vEyePt;				//!<�J�����̎��_�B
	D3DXVECTOR3				vLookatPt;			//!<�J�����̒����_�B
	D3DXVECTOR3				vUpVec;				//!<�J�����̏�����B
	D3DXVECTOR3				toPos;				//!<���_���璍���_�̃x�N�g��
	D3DXVECTOR3				cameradir;			//!<�J�����̕���
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CSkyCamera();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~CSkyCamera();
	//�A�X�y�N�g���ݒ�B
	void SetAspect(const float& _aspect)
	{
		aspect = _aspect;
	}
	//�A�X�y�N�g����擾�B
	const float& GetAspect() const
	{
		return aspect;
	}
	//�t�@�[��ݒ�B
	void SetFar(const float& _far)
	{
		Far = _far;
	}
	//�j�A�[�̎擾�B
	const float& GetNear() const
	{
		return Near;
	}
	//�t�@�[�̎擾�B
	const float& GetFar() const
	{
		return Far;
	}
	//�j�A�[��ݒ�B
	void SetNear(const float& _near)
	{
		Near = _near;
	}
	//���_�̃Z�b�^�[
	void SetEyePt(const D3DXVECTOR3& pt)
	{
		vEyePt = pt;
	}
	//���_�̃Q�b�^�[
	const D3DXVECTOR3& GetEyePt() const
	{
		return vEyePt;
	}
	//�����_�̃Z�b�^�[
	void SetLookatPt(const D3DXVECTOR3& pt)
	{
		vLookatPt = pt;
	}
	//�����_�̃Q�b�^�[�B
	const D3DXVECTOR3& GetLookatPt() const
	{
		return vLookatPt;
	}
	//������̃Z�b�^�[
	void SetUpVec(const D3DXVECTOR3& up)
	{
		vUpVec = up;
	}
	//������̃Q�b�^�[
	const D3DXVECTOR3& GetUpVec() const
	{
		return vUpVec;
	}
	//�r���[�s��̃Z�b�^�[�B
	void SetViewMatrix(const D3DXMATRIX& mView)
	{
		viewMatrix = mView;
	}
	//�r���[�s��̃Q�b�^�[
	const D3DXMATRIX& GetViewMatrix() const
	{
		return viewMatrix;
	}
	//��]�s��̋t�s��Q�b�^�[
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return viewMatrixRotInv;
	}
	//�v���W�F�N�V�����s��̃Z�b�^�[
	void SetProjectionMatrix(const D3DXMATRIX& mProj)
	{
		projectionMatrix = mProj;
	}
	//�v���W�F�N�V�����s��̃Q�b�^�[
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return projectionMatrix;
	}
	//��]�̃Q�b�^�[
	const D3DXMATRIX& GetRot() const
	{
		return rot;
	}
	/*!
	*@brief	�J��������]�B
	*/
	void RotTransversal(float roty);
	/*!
	*@brief	�J�����c��]�B
	*/
	void RotLongitudinal(float rotx);
	/*!
	*@brief	�J�����̍X�V�����B
	*/
	const D3DXVECTOR3& GetCSkyCameraDir() const
	{
		return cameradir;
	}
	void Update();
	/*!
	*@brief	�J�����̏������B
	*/
	void Init();
};