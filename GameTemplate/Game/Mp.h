#pragma once

class Game;

/// <summary>
/// マジックポイント
/// </summary>
class Mp :public IGameObject
{
public:

	/// <summary>
	/// 値を加算
	/// </summary>
	/// <param name="addMp"></param>
	void AddMp(const float addMp) 
	{
		m_mp += addMp;
		if (m_mp >= 100) {
			m_mp = 100;
		}
	}

	/// <summary>
	/// 値を減算
	/// </summary>
	/// <param name="subMp"></param>
	void SubMp(const float subMp) 
	{
		m_mp -= subMp;
		if (m_mp < 0)
		{
			m_mp = 0;
		}
	}

	/// <summary>
	/// MPを取得
	/// </summary>
	/// <returns></returns>
	float GetMP() const {
		return m_mp;
	}

	Mp();
	~Mp();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// MPバーの表示を管理
	/// </summary>
	void Cut();

	/// <summary>
	/// MPを自然回復させる
	/// </summary>
	void Heal();

	SpriteRender m_mpBar;
	SpriteRender m_mpBarGray;
	SpriteRender m_mpFrame;
	SpriteRender m_mpFrameGray;

	Game* m_game;

	float m_mp = 100.0f;
	float m_timer = 0.0f;
};

