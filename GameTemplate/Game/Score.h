#pragma once

using namespace std;

class Score : public IGameObject
{
public:

	bool Start() override;
	void Update();
	void Render(RenderContext& rc);

private:

	FontRender m_fontRender;
	wstring m_text;
	int m_score = 0;
	float m_timer = 0.0f;
};

