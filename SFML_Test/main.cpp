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
#include "Entity.h"



void SpawnEntity(size_t size, Manager& manager) {
    sf::Texture texture;
    if (!texture.loadFromFile("C:\\Users\\zian\\Downloads\\dirt.jpg")) {
        std::cerr << "Erreur: Impossible de charger la texture" << std::endl;
    }

    for (size_t i = 0; i < size; i++) {
        // Créer une entité avec la forme spécifiée
        Entity* entity = nullptr;


        entity = manager.CreateEntity(texture,sf::Vector2f(50.f, 50.f));
        


        if (entity) {
            // Position aléatoire
            float randomX = static_cast<float>(std::rand() % 750);
            float randomY = static_cast<float>(std::rand() % 550);
            entity->SetPosition(randomX, randomY);

            entity->SetSize(50.0f, 50.0f);
        }
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
    Manager manager;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "caca");
    sf::Clock clock;
    sf::Font font;
    font.openFromFile("Bebas-Regular.ttf");


    sf::Text fpsText(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White); 
    fpsText.setPosition(sf::Vector2f(10.f, 10.f)); 

    SpawnEntity(1, manager);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        manager.Update(deltaTime);
        
        int fps = static_cast<int>(1.0f / deltaTime);

        fpsText.setString("FPS: " + std::to_string(fps));

        window.clear();
        manager.Draw(window);
        window.draw(fpsText);

        window.display();

 
    }
}