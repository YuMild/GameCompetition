#pragma once

#include "camera/SpringCamera.h"

class Player;

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

	//参照
	Player* m_player;
	SpringCamera m_springCamera;
};