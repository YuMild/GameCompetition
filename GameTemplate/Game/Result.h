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
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/// <summary>
	/// Stateの管理
	/// </summary>
	void ManageState();

private:

	SpriteRender		m_resultBackGroundRender;						//	リザルト背景
	SpriteRender		m_resultRender;									//	リザルト
	SpriteRender		m_timeRender;									//	タイム
	SpriteRender		m_puddingRender;								//	プリン
	SpriteRender		m_totalScoreRender;								//	トータルスコア

	//	ランク画像
	SpriteRender		m_sRender;										//	S
	SpriteRender		m_aRender;										//	A
	SpriteRender		m_bRender;										//	B
	SpriteRender		m_cRender;										//	C
	SpriteRender		m_dRender;										//	D

	SoundSource*		m_drumRollSE			= nullptr;
	SoundSource*		m_drumSE				= nullptr;

	FontBlueNumber*		m_timeScoreFont			= nullptr;				//	タイムスコア
	FontBlueNumber*		m_puddingScoreFont		= nullptr;				//	プリンスコア
	FontPurpleNumber*	m_totalScoreFont		= nullptr;				//	トータルスコア
	Game*				m_game					= nullptr;
	Pudding*			m_pudding				= nullptr;
	Score*				m_score					= nullptr;

	int					m_1						= 0;
	int					m_10					= 0;
	int					m_100					= 0;
	int					m_1000					= 0;
	int					m_10000					= 0;

	int					m_resultState			= 0;

	bool				m_isStart4				= true;
	bool				m_isStart5				= true;
	bool				m_isStart6				= true;

	float				m_timeScore				= 0.0f;
	float				m_puddingScore			= 0.0f;
	float				m_totalScore			= 0.0f;

	float				m_stateTimer			= 0.0f;
};