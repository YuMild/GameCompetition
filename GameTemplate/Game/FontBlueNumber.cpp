#include "stdafx.h"
#include "FontBlueNumber.h"

namespace
{
	const float SQUARE_WIDTH = 1000.0f;
	const float SQUARE_HEIGHT = 1000.0f;
	const float POSITION_SLIDE = 90.0f;
}

FontBlueNumber::FontBlueNumber()
{

}

FontBlueNumber::~FontBlueNumber()
{

}

bool FontBlueNumber::Start()
{
	return true;
}

void FontBlueNumber::Init(int number)
{
	std::string text;
	text = std::to_string(number);

	int digit = text.length();

	std::string filePath;

	for (int i = 0; i < digit; i++)
	{
		char a = text[i];
		filePath = "Assets/sprite/Result/BlueNumber/";
		filePath += a;
		filePath += ".DDS";

		std::unique_ptr<SpriteRender> aRender;
		aRender = std::make_unique<SpriteRender>();
		aRender->Init(filePath.c_str(), SQUARE_WIDTH,SQUARE_HEIGHT);

		m_fontBlueNumberList.push_back(std::move(aRender));
	}
}

void FontBlueNumber::Update()
{
	int j = 0;
	for (int i = m_fontBlueNumberList.size() - 1; i >= 0; i--)
	{
		m_fontBlueNumberList[i]->SetPosition({ m_position.x - POSITION_SLIDE * j, m_position.y, m_position.z });
		m_fontBlueNumberList[i]->SetScale(m_scale);
		m_fontBlueNumberList[i]->Update();
		j++;
	}
}

void FontBlueNumber::Render(RenderContext& rc)
{
	for (int i = 0; i < m_fontBlueNumberList.size(); i++)
	{
		m_fontBlueNumberList[i]->Draw(rc);
	}
}