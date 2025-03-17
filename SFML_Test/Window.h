#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Text.h"


class Manager;
class Window
{
private:
	sf::RenderWindow* mWindow = nullptr;
	sf::Clock mClock;

	float mWidth = 0;
	float mHeight = 0;

	float mDeltaTime = 0;
	int mFPS = 0;

	Manager* mManager = nullptr;
	TextManager mTextManager;

public:
	Window(Manager* manager);
	~Window();

	void CreateWindow(int x, int y, const std::string& windowName);

	void Draw(const sf::Drawable& drawable);
	void Update();
	void UpdateDeltaTime();

	bool IsOpen() { return mWindow->isOpen(); }
	bool HasFocus() { return mWindow->hasFocus(); }

	const float& GetDeltaTime() { return mDeltaTime; }
	const int& GetFPS();
	sf::RenderWindow& GetWindow() { return *mWindow; }
	TextManager& GetTextManager() { return mTextManager; }

	void Clear();
	void SetVSync(bool enable){ mWindow->setVerticalSyncEnabled(enable); }
	void SetFPS(int fps){ mWindow->setFramerateLimit(fps); }

	void RunLoop();

};

