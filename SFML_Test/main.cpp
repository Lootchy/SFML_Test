﻿#include <SFML/Graphics.hpp>
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
#include "TextureManager.h"
#include "Window.h"
#include "Player.h"
#include "Text.h"



void SpawnEntity(size_t size, Manager& manager) {
    
    for (size_t i = 0; i < size; i++) {
        Entity* entity = manager.CreateEntity<Player>("dirt", sf::Vector2f(10.f, 10.f), &manager);
        if (entity) {
            float randomX = static_cast<float>(std::rand() % 750);
            float randomY = static_cast<float>(std::rand() % 550);
            entity->SetPosition(randomX, randomY);
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
    Manager manager(800, 600);
    Window window(&manager);
    TextureManager::loadTexture("dirt", "dirt.jpg");
    TextureManager::loadTexture("base", "whitesquare.png");
    Player* player = manager.CreateEntity<Player>("base", sf::Vector2f(10.f, 10.f), &manager);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    window.CreateWindow( 800, 600, "caca");
    sf::Font font;
    font.openFromFile("Bebas-Regular.ttf");


    sf::Text fpsText(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White); 
    fpsText.setPosition(sf::Vector2f(10.f, 10.f)); 

    Text* myText = new Text();
    myText->SetFont("Bebas-Regular.ttf");
    myText->SetString("Hello, SFML!");
    myText->SetSize(30);
    myText->SetColor(sf::Color::White);
    myText->SetPosition(100, 100);

    window.GetTextManager().AddText(myText);
    SpawnEntity(5000, manager);

    window.RunLoop();
}