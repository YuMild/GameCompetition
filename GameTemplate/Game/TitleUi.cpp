#include "stdafx.h"
#include "TitleUi.h"
TitleUi::TitleUi() {

}
TitleUi::~TitleUi() {

}
bool TitleUi::Start()
{
	/*m_heart1.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_heart1.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_heart1.Update();
	m_heart2.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_heart2.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_heart2.Update();
	m_heart3.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_heart3.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_heart3.Update();
	m_fire1.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_fire1.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_fire1.Update();
	m_fire2.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_fire2.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_fire2.Update();
	m_water1.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_water1.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_water1.Update();
	m_water2.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_water2.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_water2.Update();
	m_wind1.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_wind1.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_wind1.Update();
	m_wind2.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_wind2.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_wind2.Update();
	m_shine1.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_shine1.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_shine1.Update();
	m_shine2.Init("Assets/sprite/TypeHeart1", 200.0f, 200.0f);
	m_shine2.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_shine2.Update();*/

	return true;
}

void TitleUi::Update()
{
	m_heart1.Update();
	State();
	Move();
}

void TitleUi::State()
{
}

void TitleUi::Move() 
{
	m_up += 0.1f;
}

void TitleUi::Render(RenderContext& rc)
{
	m_heart1.Draw(rc);
}