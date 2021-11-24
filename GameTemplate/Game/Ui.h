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
	//マップ
	SpriteRender m_mapBackGround;
	SpriteRender m_mapGradation;
	SpriteRender m_mapFrame;
	SpriteRender m_playerMap;
	//時計
	SpriteRender m_clockBackGround;
	SpriteRender m_clockFrame;
	SpriteRender m_clockMinuteHund;
	SpriteRender m_clockSecondHund;

	SpriteRender m_typeFire;
	SpriteRender m_typeWater;
	SpriteRender m_typeWind;
	SpriteRender m_typeShine;

	SpriteRender m_typeFireCoolTime;
	SpriteRender m_typeWaterCoolTime;
	SpriteRender m_typeWindCoolTime;
	SpriteRender m_typeShineCoolTime;

	SpriteRender m_mpBar;
	SpriteRender m_mpFrame;

	Vector3 m_playerMapPosition;
	Vector3 m_enemyMapPosition;

	Enemy* m_enemy;
	Player* m_player;
};

