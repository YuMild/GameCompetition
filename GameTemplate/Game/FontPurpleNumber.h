#pragma once

using namespace std;

class FontPurpleNumber : public IGameObject
{
public:

	FontPurpleNumber();
	~FontPurpleNumber();
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

	//�ϒ��z��
	std::vector<std::unique_ptr<SpriteRender>>m_fontPurpleNumberList;

	Vector3 m_position;
	Vector3 m_scale;
};