#pragma once

class Fade;
class TitleUi;

/// <summary>
/// タイトル
/// </summary>
class Title : public IGameObject
{
public:

	Title();
	~Title();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/// <summary>
	/// ステート
	/// </summary>
	void State();

	/// <summary>
	/// タイマー
	/// </summary>
	void Timer();

private:

	//背景
	SpriteRender		m_titleRender;

	//PressStart
	SpriteRender		m_pressStartRender;

	//アイコン
	//数字が小さい程手前に
	SpriteRender		m_heart1;						//ハート
	SpriteRender		m_heart2;				
	SpriteRender		m_heart3;				
	SpriteRender		m_fire1;						//炎
	SpriteRender		m_fire2;
	SpriteRender		m_water1;						//水
	SpriteRender		m_water2;
	SpriteRender		m_wind1;						//風
	SpriteRender		m_wind2;
	SpriteRender		m_shine1;						//光
	SpriteRender		m_shine2;

	//ポジション
	Vector3				m_heart1Position;				//ハート
	Vector3				m_heart2Position;
	Vector3				m_heart3Position;
	Vector3				m_fire1Position;				//炎
	Vector3				m_fire2Position;
	Vector3				m_water1Position;				//水
	Vector3				m_water2Position;
	Vector3				m_wind1Position;				//風
	Vector3				m_wind2Position;
	Vector3				m_shine1Position;				//光
	Vector3				m_shine2Position;

	//音声
	SoundSource*		m_titleBGM		= nullptr;		//背景
	SoundSource*		m_buttonSE;						//ボタンが押された時

	Fade*				m_fade			= nullptr;
	TitleUi*			m_titleUi		= nullptr;

	bool				m_isWaitFadeOut	= false;
	float				m_alpha			= 0.0f;

	//アイコンを上下に動かせる
	float				m_timer1		= 0;
	float				m_upDown1		= 0;
	float				m_timer2		= 0;
	float				m_upDown2		= 0;
	float				m_timer3		= 0;
	float				m_upDown3		= 0;
	float				m_timer4		= 0;
	float				m_upDown4		= 0;
	float				m_timer5		= 0;
	float				m_upDown5		= 0;
};