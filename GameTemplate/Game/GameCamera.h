#pragma once

class Player;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	float stickx;
	float sticky;
	Vector3 target;
	Vector3 pos;
	Vector3 position;
	Vector3 toCameraPosOld;
	Vector3 toPosDir;
	Vector3 m_toCameraPos = Vector3::One;
	Player* m_player;
};

