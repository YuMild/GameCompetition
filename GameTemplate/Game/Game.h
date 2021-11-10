#pragma once

#include "Level3DRender/LevelRender.h"
#include "sound/SoundSource.h"

class Enemy;
class Game;
class Player;
class BackGround;
class GameCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int levelfont = 0;
	int hp = 3;
	float level = 0;
	float timer = 0;
	float cleartimer = 0;
	float spawntimer = 0;
	float deletetimer = 0;
	bool spawntime = true;
	bool hp0 = true;
	bool hp1 = true;
	bool hp2 = true;

	//モデル
	ModelRender m_modelRender;

	//メンバ
	Enemy* m_enemy;
	Player* m_player;
	GameCamera* m_gameCamera;
	BackGround* m_backGround;

	//フォント
	FontRender limitFont;
	FontRender levelFont;

	//画像
	SpriteRender frameRender;
	SpriteRender hpgreenRender;
	SpriteRender hpdeathgreenRender;
	SpriteRender hpyellowRender;
	SpriteRender hpdeathyellowRender;
	SpriteRender hpredRender;
	SpriteRender hpdeathredRender;

	//ポジション
	Vector3 frameposition;

	//音声
	SoundSource* damage1SE;
	SoundSource* damage2SE;
	SoundSource* damage3SE;
};