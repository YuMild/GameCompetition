#include "stdafx.h"
#include "GameCamera.h"

#include "Game.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//	プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");
	m_toCameraPos.Set(0.0f, 70.0f, 100.0f);

	//	ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,		//	ばねカメラの処理を行うカメラを指定する
		10000.0f,			//	カメラの移動速度の最大値
		true,				//	カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う
		5.0f				//	カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる
	);

	m_toCameraPos.y -= 50.0f;

	m_game = FindGO<Game>("game");

	return true;
}

void GameCamera::Update()
{
	if (m_game->GetManageState() != 0)
	{
		return;													//	早期リターン
	}
	//	カメラを更新
	//	注視点を計算する
	m_target = m_player->GetPosition();

	//	プレイヤの足元からちょっと上を注視点とする。
	m_target.y += 70.0f;
	m_target += g_camera3D->GetForward() * 10.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	パッドの入力を使ってカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//	Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);

	//	X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);

	//	カメラの回転の上限をチェックする
	//	注視点から視点までのベクトルを正規化する
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;							//	カメラが上に向き過ぎるのを防ぐ
	}
	else if (toPosDir.y > 0.8f) {
		m_toCameraPos = toCameraPosOld;							//	カメラが下に向き過ぎるのを防ぐ
	}

	//	視点を計算する
	Vector3 pos = m_target + m_toCameraPos;

	//	バネカメラに注視点と視点を設定する
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);

	//	カメラの更新
	m_springCamera.Update();

}