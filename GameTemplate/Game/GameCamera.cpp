#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<Player>("player");
	m_toCameraPos.Set(0.0f, 70.0f, 100.0f);

	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��
		10000.0f,				//�J�����̈ړ����x�̍ő�l
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s��
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�
	);

	m_toCameraPos.y -= 100.0f;

	return true;
}

void GameCamera::Update()
{
	//�J�������X�V
	//�����_���v�Z����
	m_target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	m_target.y += 70.0f;
	m_target += g_camera3D->GetForward() * 10.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����
	//�����_���王�_�܂ł̃x�N�g���𐳋K������
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ�������
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J���������������
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J����������������
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����
	Vector3 pos = m_target + m_toCameraPos;

	//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);

	//�J�����̍X�V
	m_springCamera.Update();
}