#pragma once

class FontBlueNumber;
class FontPurpleNumber;
class Game;
class Pudding;
class Score;

/// <summary>
/// リザルト
/// </summary>
class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// Stateの管理
	/// </summary>
	void ManageState();

private:

	SpriteRender m_resultBackGroundRender;						//	リザルト背景
	SpriteRender m_resultRender;								//	リザルト
	SpriteRender m_timeRender;									//	タイム
	SpriteRender m_puddingRender;								//	プリン
	SpriteRender m_totalScoreRender;							//	トータルスコア

	//	ランク画像
	SpriteRender m_sRender;										//	S
	SpriteRender m_aRender;										//	A
	SpriteRender m_bRender;										//	B
	SpriteRender m_cRender;										//	C
	SpriteRender m_dRender;										//	D

	SoundSource* m_drumRollSE;
	SoundSource* m_drumSE;

	FontBlueNumber* m_timeScoreFont;							//	タイムスコア
	FontBlueNumber* m_puddingScoreFont;							//	プリンスコア
	FontPurpleNumber* m_totalScoreFont;							//	トータルスコア
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