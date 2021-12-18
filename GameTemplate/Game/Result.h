#pragma once
class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	int m_1;
	int	m_10;
	int m_100;
	int m_1000;
	int m_10000;

};