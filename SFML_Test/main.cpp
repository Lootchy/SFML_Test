#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <cstdlib> 
#include <ctime>   
#include <execution>
#include "BounceBall.h"



void SpawnBall(size_t size, std::deque<BounceBall>& arrayBall) {
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

void Update(std::deque<BounceBall>& ball, sf::VertexArray& particles) {
    int i = 0;
    for (BounceBall& temp : ball) {
        const sf::RectangleShape& shape = temp.GetShape();
        const sf::Vector2f& pos = shape.getPosition();
        const sf::Vector2f& size = shape.getSize();
        const sf::Color& color = shape.getFillColor();


        int baseIndex = i * 6;
        sf::Vertex* v = &particles[baseIndex];  

        
        v[0].position = pos;
        v[1].position = pos + sf::Vector2f(size.x, 0);
        v[2].position = pos + sf::Vector2f(size.x, size.y);

        
        v[3].position = pos;
        v[4].position = pos + sf::Vector2f(size.x, size.y);
        v[5].position = pos + sf::Vector2f(0, size.y);


        for (int j = 0; j < 6; j++) {
            v[j].color = color;
        }

        i++;
    }
}


int main()
{
    size_t size = 200000;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "caca");
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

    std::deque<BounceBall> mBall;
    SpawnBall(size, mBall);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();


        std::for_each(std::execution::par_unseq, mBall.begin(), mBall.end(), [&](BounceBall& ball) {
            ball.Update(deltaTime);
            });

        Update(mBall, particles);
        
        int fps = static_cast<int>(1.0f / deltaTime);

        fpsText.setString("FPS: " + std::to_string(fps));

        window.clear();

        window.draw(particles);
        window.draw(fpsText);

        window.display();
    }
}