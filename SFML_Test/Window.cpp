
#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
	if (mWindow)
	{
		delete mWindow;
		mWindow = nullptr;
	}
}

void Window::CreateWindow(int x, int y, const std::string& windowName)
{
	if (!mWindow)
		mWindow = new sf::RenderWindow();
	mWindow->create(sf::VideoMode(sf::Vector2u(x, y)), windowName);
}

void Window::Clear()
{
	mWindow->clear();
}

void Window::Draw(const sf::Drawable& drawable)
{
	mWindow->draw(drawable);
}


void Window::Display()
{
	mWindow->display();
}

const int& Window::GetFPS()
{
	mFPS = static_cast<int>(1.0f / mDeltaTime);
	return mFPS;
}

void Window::SetDeltaTime()
{
	 mDeltaTime = mClock.restart().asSeconds();
}

