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

	//カメラを更新。
	//注視点を計算する。
	target = m_player->playerposition;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 50.0f;
	target += g_camera3D->GetForward() * 20.0f;//弄らない方がいいかも

	toCameraPosOld = m_toCameraPos;

	//パッドの入力を使ってカメラを回す。
	stickx = g_pad[0]->GetRStickXF();
	sticky = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 3.0f * stickx);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 0.0f * sticky);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	pos = target + m_toCameraPos;//視点を計算する。

	g_camera3D->SetPosition(pos);//座標と注視点を設定。
	g_camera3D->SetTarget(target);
	g_camera3D->Update();	//カメラの更新。
}