#pragma once

using namespace std;

class FontPurpleNumber : public IGameObject
{
public:

	FontPurpleNumber();
	~FontPurpleNumber();
	bool Start();

	/// <summary>
	/// 表示させたい数字を入力
	/// </summary>
	/// <param name="number"></param>
	void Init(int number);

	/// <summary>
	/// ポジションを指定できる
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// サイズを指定できる
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void Update();
	void Render(RenderContext& rc);

private:

	std::vector<std::unique_ptr<SpriteRender>>m_fontPurpleNumberList;		//可変長配列

	Vector3 m_position;
	Vector3 m_scale;
};