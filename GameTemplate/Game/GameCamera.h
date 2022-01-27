#pragma once

#include "camera/SpringCamera.h"

class Game;
class Player;

/// <summary>
/// カメラ
/// </summary>
class GameCamera : public IGameObject
{
public:

	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:

	//ベクトル
	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_toCameraPos = Vector3::One;

	//クラス
	Game* m_game;
	Player* m_player;
	SpringCamera m_springCamera;
};