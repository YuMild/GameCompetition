#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera() {

}

GameCamera::~GameCamera() {

}

bool GameCamera::Start() {
	m_player = FindGO<Player>("player");
	position = m_player->playerposition;
	return true;
}

void GameCamera::Update() {

	//�J�������X�V�B
	//�����_���v�Z����B
	target = m_player->playerposition;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;
	target += g_camera3D->GetForward() * 20.0f;//�M��Ȃ�������������

	toCameraPosOld = m_toCameraPos;

	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	stickx = g_pad[0]->GetRStickXF();
	sticky = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 3.0f * stickx);
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 0.0f * sticky);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	pos = target + m_toCameraPos;//���_���v�Z����B

	g_camera3D->SetPosition(pos);//���W�ƒ����_��ݒ�B
	g_camera3D->SetTarget(target);
	g_camera3D->Update();	//�J�����̍X�V�B
}