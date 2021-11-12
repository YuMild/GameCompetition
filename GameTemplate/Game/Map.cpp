#include "stdafx.h"
#include "Map.h"

namespace
{
	Vector3 MAP_ORIGIN = Vector3(640.0f, 220.0f, 0.0f);
}

Map::Map() {

}
Map::~Map() {

}
bool Map::Start() {

	map.Init("Assets/sprite/Map.dds", 300.0f, 300.0f);
	map.SetPosition({ 790.0f,370.0f,0.0f });
	map.Update();
	mapFrame.Init("Assets/sprite/MapFrame.dds", 300.0f, 300.0f);
	mapFrame.SetPosition({ 790.0f,370.0f,0.0f });
	mapFrame.Update();
	
	return true;
}
void Map::Update() {

}
void Map::Render(RenderContext& rc) {
	map.Draw(rc);
	mapFrame.Draw(rc);
}