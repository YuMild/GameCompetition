#pragma once

class Enemy;
class Player;

class Ui :public IGameObject
{
public:
	Ui();
	~Ui();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//ƒ}ƒbƒv
	SpriteRender m_mapBackGround;
	SpriteRender m_mapGradation;
	SpriteRender m_mapFrame;
	SpriteRender m_playerMap;

	SpriteRender m_typeFire;
	SpriteRender m_typeWater;
	SpriteRender m_typeWind;
	SpriteRender m_typeShine;
	SpriteRender m_hpBar;

	Vector3 m_playerMapPosition;
	Vector3 m_enemyMapPosition;

	Enemy* m_enemy;
	Player* m_player;
};

