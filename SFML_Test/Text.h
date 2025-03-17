#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Text
{
private:
	sf::Font mFont;
	sf::Text mText;

public:
	Text(const std::string& fontPath = "Bebas-Regular.ttf");

	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

	const sf::Text& GetText() { return mText; }

	void SetFont(std::string filepath);
	void SetPosition(float x, float y);
	void SetSize(float size);
	void SetColor(sf::Color color);
	void SetString(const std::string& str) { mText.setString(str); }

};


class TextManager 
{
private:
	std::vector<Text*> mTexts;

public:
	void Update();
	void Draw(sf::RenderWindow& window);

	void AddText(Text* text) { mTexts.push_back(text); }
	const std::vector<Text*>& GetTexts() { return mTexts; }
};

