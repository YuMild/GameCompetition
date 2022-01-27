#include "stdafx.h"
#include "Hp.h"
#include "Game.h"

namespace
{
	const float HP_WIDTH = 100.0f;
	const float HP_HEIGHT = 100.0f;

	const float HP_LEFT_POSITION = -600.0f;
	const float HP_CENTER_POSITION = -480.0f;
	const float HP_RIGHT_POSITION = -360.0f;

	const float HP_Y_POSITION = -290.0f;
}

Hp::Hp()
{

}

Hp::~Hp() 
{

}

bool Hp::Start()
{
	Vector3 positionList[3];
	positionList[0] = Vector3(HP_LEFT_POSITION, HP_Y_POSITION, 0.0f);
	positionList[1] = Vector3(HP_CENTER_POSITION, HP_Y_POSITION, 0.0f);
	positionList[2] = Vector3(HP_RIGHT_POSITION, HP_Y_POSITION, 0.0f);

	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Init("Assets/sprite/Hp/HPInside.DDS", HP_WIDTH, HP_HEIGHT);
		m_hpInside[m_num].SetPosition(positionList[m_num]);
		m_hpInside[m_num].Update();
		m_hpFrame[m_num].Init("Assets/sprite/Hp/HPFrame.DDS", HP_WIDTH, HP_HEIGHT);
		m_hpFrame[m_num].SetPosition(positionList[m_num]);
		m_hpFrame[m_num].Update();
		m_hpFrameGray[m_num].Init("Assets/sprite/Hp/HPGray.DDS", HP_WIDTH, HP_HEIGHT);
		m_hpFrameGray[m_num].SetPosition(positionList[m_num]);
		m_hpFrameGray[m_num].Update();
	}

	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/Damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/Damage3.wav");

	m_game = FindGO<Game>("game");

	return true;
}

void Hp::Update()
{
	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Update();
	}
	
	for (m_num = 0; m_num < m_hpFrameNum; m_num++)
	{
		m_hpFrame[m_hpFrameNum].Update();
	}
	Damage();
}

void Hp::Render(RenderContext& rc) 
{
	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Draw(rc);
	}

	for (m_num = 0; m_num < m_hpFrameGrayNum; m_num++)
	{
		m_hpFrameGray[m_num].Draw(rc);
	}

	if (m_game->GetManageState() == 0)
	{
		for (m_num = 0; m_num < m_hpFrameNum; m_num++)
		{
			m_hpFrame[m_num].Draw(rc);
		}
	}
}

void Hp::Damage()
{
	if (m_hp == 2 && m_damage1Judge) {
		m_damage1SE = NewGO<SoundSource>(8);
		m_damage1SE->Init(8);
		m_damage1SE->Play(false);
		m_damage1Judge = false;
	}
	else if (m_hp == 1 && m_damage2Judge) {
		m_damage1SE = NewGO<SoundSource>(9);
		m_damage1SE->Init(9);
		m_damage1SE->Play(false);
		m_damage2Judge = false;
	}
	else if (m_hp == 0 && m_damage3Judge) {
		m_damage1SE = NewGO<SoundSource>(10);
		m_damage1SE->Init(10);
		m_damage1SE->Play(false);
		m_damage3Judge = false;
	}
}