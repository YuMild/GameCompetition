#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Enemy;
class GameCamera;
class GameOver;
class Map;
class Player;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void ManageState();

private:
	ModelRender m_modelRender;
	BackGround* m_backGround;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	Map* m_map;
	Player* m_player;
	SkyCube* m_skyCube;
	SoundSource* m_damage1SE;
	SoundSource* m_damage2SE;
	SoundSource* m_damage3SE;
	int m_levelFont = 0;
	int m_hp = 3;
	float m_timer = 0;
	float m_level = 0;
	float m_spawnTimer = 0;
	bool m_1Damage = true;
	bool m_2Damage = true;
	bool m_3Damage = true;
};

