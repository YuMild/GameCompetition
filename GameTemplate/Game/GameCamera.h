#pragma once

#include "camera/SpringCamera.h"

class Game;
class Player;

class GameCamera : public IGameObject
{
public:

	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:

	//�x�N�g��
	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_toCameraPos = Vector3::One;

	//�Q��
	Game* m_game;
	Player* m_player;
	SpringCamera m_springCamera;
};