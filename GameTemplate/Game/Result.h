#pragma once

class FontBlueNumber;
class FontPurpleNumber;
class Game;
class Pudding;
class Score;

class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void ManageState();

private:

	SpriteRender m_resultBackGroundRender;
	SpriteRender m_resultRender;
	SpriteRender m_timeRender;
	SpriteRender m_puddingRender;
	SpriteRender m_totalScoreRender;

	SpriteRender m_sRender;
	SpriteRender m_aRender;
	SpriteRender m_bRender;
	SpriteRender m_cRender;
	SpriteRender m_dRender;

	SoundSource* m_drumRollSE;
	SoundSource* m_drumSE;

	FontBlueNumber* m_timeNumber;
	FontBlueNumber* m_puddingNumber;
	FontPurpleNumber* m_fontPurpleNumber;
	Game* m_game;
	Pudding* m_pudding;
	Score* m_score;

	int m_1;
	int	m_10;
	int m_100;
	int m_1000;
	int m_10000;

	int m_resultState = 0;

	bool m_isStart4 = true;
	bool m_isStart5 = true;
	bool m_isStart6 = true;

	float m_timeScore = 0.0f;
	float m_puddingScore = 0.0f;
	float m_totalScore = 0.0f;

	float m_stateTimer = 0.0f;
};