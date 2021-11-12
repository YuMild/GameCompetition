#pragma once
class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender map;
	SpriteRender mapFrame;
};

