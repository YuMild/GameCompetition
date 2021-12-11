#include "stdafx.h"
#include "Hp.h"

Hp::Hp() {

}

Hp::~Hp() {

}

bool Hp::Start()
{
	Vector3 positionList[3];
	positionList[0] = Vector3(-600.0f, -290.0f, 0.0f);
	positionList[1] = Vector3(-480.0f, -290.0f, 0.0f);
	positionList[2] = Vector3(-360.0f, -290.0f, 0.0f);

	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Init("Assets/sprite/HPInside.DDS", 100.0f, 100.0f);
		m_hpInside[m_num].SetPosition(positionList[m_num]);
		m_hpInside[m_num].Update();
		m_hpFrame[m_num].Init("Assets/sprite/HPFrame.DDS", 100.0f, 100.0f);
		m_hpFrame[m_num].SetPosition(positionList[m_num]);
		m_hpFrame[m_num].Update();
	}

	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/Damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/Damage3.wav");

	return true;
}

void Hp::Update()
{
	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Update();
	}
	for (m_num = 0; m_num < m_frameNum; m_num++)
	{
		m_hpFrame[m_frameNum].Update();
	}
	Damage();
}

void Hp::Render(RenderContext& rc) 
{
	for (m_num = 0; m_num < m_hp; m_num++)
	{
		m_hpInside[m_num].Draw(rc);
	}
	for (m_num = 0; m_num < m_frameNum; m_num++)
	{
		m_hpFrame[m_num].Draw(rc);
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