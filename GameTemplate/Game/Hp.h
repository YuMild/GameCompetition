#pragma once

class Game;

/// <summary>
/// ヒットポイント
/// </summary>
class Hp :public IGameObject
{
public:

	/// <summary>
	/// 値を減算
	/// </summary>
	/// <param name="subHp"></param>
	void SubHP(const int subHp)
	{
		m_hp -= subHp;
	}

	/// <summary>
	/// HPを指定
	/// </summary>
	/// <param name="setHp"></param>
	/// <returns></returns>
	int SetHP(const int setHp)
	{
		m_hp = setHp;
		return m_hp;
	}

	/// <summary>
	/// HPの値を取得
	/// </summary>
	/// <returns></returns>
	int GetHP() const
	{
		return m_hp;
	}

	Hp();
	~Hp();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	
private:

	/// <summary>
	/// ダメージを管理
	/// </summary>
	void Damage();

	//画像
	SpriteRender		m_hpInside[3];
	SpriteRender		m_hpFrame[3];
	SpriteRender		m_hpFrameGray[3];

	//音声
	SoundSource*		m_damage1SE			= nullptr;
	SoundSource*		m_damage2SE			= nullptr;
	SoundSource*		m_damage3SE			= nullptr;

	Game*				m_game				= nullptr;

	//一度だけ判定を取る
	bool				m_damage1Judge		= true;
	bool				m_damage2Judge		= true;
	bool				m_damage3Judge		= true;

	int					m_num				= 0;
	int					m_hpFrameNum		= 3;
	int					m_hpFrameGrayNum	= 3;
	int					m_hp				= 3;
};