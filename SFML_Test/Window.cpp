#include "Window.h"
#include "Entity.h"



Window::Window(Manager* manager) : mManager(manager)
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
	mWidth = x;
	mHeight = y;
}

void Window::Clear()
{
	mWindow->clear();
}


void Window::RunLoop()
{
	while (IsOpen())
	{
		mManager->Update(GetDeltaTime());
		mTextManager.Update();
		Clear();

		mManager->Draw(*mWindow);
		mTextManager.Draw(GetWindow());
		Update();
	}
}


void Window::Draw(const sf::Drawable& drawable)
{
	mWindow->draw(drawable);
}


void Window::Update()
{
	mWindow->display();
	UpdateDeltaTime();
}

const int& Window::GetFPS()
{
	mFPS = static_cast<int>(1.0f / mDeltaTime);
	return mFPS;
}

void Window::UpdateDeltaTime()
{
	 mDeltaTime = mClock.restart().asSeconds();
}

