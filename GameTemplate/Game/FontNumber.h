#pragma once

using namespace std;

class FontNumber : public IGameObject
{
public:

	FontNumber();
	~FontNumber();
	bool Start();
	void Init(int number);
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	void Update();
	void Render(RenderContext& rc);


private:

	//‰Â•Ï’·”z—ñ
	std::vector<std::unique_ptr<SpriteRender>>m_fontNumberList;

	Vector3 m_position;
	Vector3 m_scale;
};