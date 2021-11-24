#pragma once
class Mp :public IGameObject
{
public:
	Mp();
	~Mp();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_mpBar;
	SpriteRender m_mpFrame;
};

