#include "Text.h"



Text::Text(const std::string& fontPath) : mText(mFont)
{
	if (!mFont.openFromFile(fontPath))
	{
		throw std::runtime_error("Impossible de charger la police : " + fontPath);
	}
	mText.setFont(mFont);
	mText.setCharacterSize(20);
	mText.setFillColor(sf::Color::White);
}

void Text::SetFont(std::string filepath)
{
	if (!mFont.openFromFile(filepath)) {
		throw std::runtime_error("Impossible de charger la police : " + filepath);
	}

	mText.setFont(mFont);
}

void Text::SetPosition(float x, float y)
{
	mText.setPosition(sf::Vector2f(x, y));
}

void Text::SetSize(float size)
{
	mText.setCharacterSize(size);
}

void Text::SetColor(sf::Color color)
{
	mText.setFillColor(color);
}

void TextManager::Update()
{
	for (auto& t : GetTexts()) {
		t->Update();
	}
}

void TextManager::Draw(sf::RenderWindow& window)
{
	for (auto& t : GetTexts()) {
		window.draw(t->GetText());
	}
}
