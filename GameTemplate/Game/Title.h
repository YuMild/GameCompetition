#pragma once
class Title : public IGameObject
{
private:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//�摜
	SpriteRender title;
	SpriteRender cursor;
	SpriteRender start;
	SpriteRender help;

	Vector3 cursorPosition;
	Vector3 startPosition;
	Vector3 helpPosition;

	int titleState = 0;
};

