#include "stdafx.h"
#include "FontPurpleNumber.h"

namespace
{
	const float SQUARE_WIDTH	= 1000.0f;
	const float SQUARE_HEIGHT	= 1000.0f;
	const float POSITION_SLIDE	= 90.0f;
}

FontPurpleNumber::FontPurpleNumber()
{

}

FontPurpleNumber::~FontPurpleNumber()
{

}

bool FontPurpleNumber::Start()
{
	return true;
}

void FontPurpleNumber::Init(int number)
{
	std::string text;
	text = std::to_string(number);

	int digit = text.length();

	std::string filePath;

	for (int i = 0; i < digit; i++)
	{
		filePath = "Assets/sprite/Result/PurpleNumber/";
		filePath += text[i];
		filePath += ".DDS";

		std::unique_ptr<SpriteRender> spriteRender;
		spriteRender = std::make_unique<SpriteRender>();
		spriteRender->Init(filePath.c_str(), SQUARE_WIDTH, SQUARE_HEIGHT);

		m_fontPurpleNumberList.push_back(std::move(spriteRender));
	}
}

void FontPurpleNumber::Update()
{
	int digit = 0;
	for (int i = m_fontPurpleNumberList.size() - 1; i >= 0; i--)
	{
		m_fontPurpleNumberList[i]->SetPosition({ m_position.x - POSITION_SLIDE * digit, m_position.y, m_position.z });
		m_fontPurpleNumberList[i]->SetScale(m_scale);
		m_fontPurpleNumberList[i]->Update();
		digit++;
	}
}

void FontPurpleNumber::Render(RenderContext& rc)
{
	for (int i = 0; i < m_fontPurpleNumberList.size(); i++)
	{
		m_fontPurpleNumberList[i]->Draw(rc);
	}
}