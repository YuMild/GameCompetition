#pragma once

using namespace std;

class FontBlueNumber : public IGameObject
{
public:

	FontBlueNumber();
	~FontBlueNumber();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;;

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

private:

	std::vector<std::unique_ptr<SpriteRender>>		m_fontBlueNumberList;		//可変長配列

	Vector3											m_position;
	Vector3											m_scale;
};