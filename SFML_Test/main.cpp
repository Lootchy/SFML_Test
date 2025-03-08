#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <cstdlib> 
#include <ctime>   
#include "BounceBall.h"



void SpawnBall(size_t size, std::list<BounceBall>& arrayBall) {
    for (size_t i = 0; i < size; i++) {
        BounceBall ball;

        float randomX = static_cast<float>(std::rand() % 750);
        float randomY = static_cast<float>(std::rand() % 550);
        ball.SetPosition(randomX, randomY);

        ball.SetBounciness(1.0f);
        sf::Color randomColor(
            static_cast<int>(std::rand() % 256),
            static_cast<int>(std::rand() % 256),
            static_cast<int>(std::rand() % 256)
        );
        ball.SetColor(randomColor);

        // Affectation de la balle dans le tableau
        arrayBall.push_back(ball);
    }
}

void Update(std::list<BounceBall>& ball, sf::VertexArray& particles) {
    int i = 0;
    for (BounceBall& temp : ball) {
        sf::Vector2f pos = temp.GetShape().getPosition();
        sf::Vector2f size = temp.GetShape().getSize();
        sf::Color color = temp.GetShape().getFillColor();

        particles[i * 6 + 0].position = pos;                      
        particles[i * 6 + 1].position = pos + sf::Vector2f(size.x, 0);  
        particles[i * 6 + 2].position = pos + sf::Vector2f(size.x, size.y); 

        particles[i * 6 + 3].position = pos;
        particles[i * 6 + 4].position = pos + sf::Vector2f(size.x, size.y);
        particles[i * 6 + 5].position = pos + sf::Vector2f(0, size.y);

        for (int j = 0; j < 6;j++) {
            particles[i * 6 + j].color = color;
        }
        i++;
    }
}

int main()
{
    size_t size = 40000;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML works!");
    sf::Clock clock;
    sf::VertexArray particles(sf::PrimitiveType::Triangles, 6 * size);
    sf::Font font;
    if (!font.openFromFile("Bebas-Regular.ttf"))
    {
        std::cerr << "Erreur de chargement de la police" << std::endl;
        return -1;
    }

    sf::Text fpsText(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White); 
    fpsText.setPosition(sf::Vector2f(10.f, 10.f)); 

    std::list<BounceBall> mBall;
    SpawnBall(size, mBall);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();


        for (BounceBall& ball : mBall) {
            ball.Update(deltaTime);
        }
        Update(mBall, particles);
        
        int fps = static_cast<int>(1.0f / deltaTime);

        fpsText.setString("FPS: " + std::to_string(fps));

        window.clear();

        window.draw(particles);
        window.draw(fpsText);


        window.display();


    }
}