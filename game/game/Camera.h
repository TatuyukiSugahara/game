#pragma once

class CPlayer;

/*!
 *@brief	�J�����N���X�B
 */
class Camera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXMATRIX				mRot;				//!<��]�s��
	D3DXMATRIX				viewMatrixRotInv;			//��]�s��̋t�s��B
	D3DXVECTOR3				vEyePt;				//!<�J�����̎��_�B
	D3DXVECTOR3				vLookatPt;			//!<�J�����̒����_�B
	D3DXVECTOR3				vUpVec;				//!<�J�����̏�����B
	D3DXVECTOR3				toPos;				//!<���_���璍���_�̃x�N�g��
	D3DXVECTOR3				cameradir;			//�J�����̕���
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
	float					bosstime;			//!<�{�X�o�ꎞ�̃J�������o�̎���
	float					Angle;				//!<��p
	float					camerahokan = 1.0f;	//!<�J�����̐��`�ۊǁB
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
		return mRot;
	}
	/*!
	*@brief	�J�����̕����Q�b�g�B
	*/
	const D3DXVECTOR3& GetCameraDir()
	{
		return cameradir;
	}
	//�J���������ɉ�]�B
	void RotTransversal(float roty);
	//�J�������c�ɉ�]�B
	void RotLongitudinal(float rotx);
	//�{�X�J����
	void BossCamera();
	/*!
	*@brief	�J�����̍X�V�B
	*/
	void Update();
	/*!
	 *@brief	�J�����̏������B
	 */
	void Init();
};