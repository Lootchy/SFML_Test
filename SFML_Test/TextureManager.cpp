#include "TextureManager.h"

TextureManager::TextureManager()
{
}

map<string, sf::Texture*> TextureManager::textures;
std::vector<string> TextureManager::order;


int TextureManager::getLength() {
    return textures.size();
}


sf::Texture* TextureManager::getTexture(string name)
{


    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    else {
        return NULL;
    }
}


sf::Texture* TextureManager::getTexture(int index)
{
    
    return getTexture(order.at(index));
}


sf::Texture* TextureManager::loadTexture(string name, string path)
{
    
    sf::Texture* texture = new sf::Texture();

    if (texture->loadFromFile(path))
    {
        textures[name] = texture;

        
        order.push_back(name);
        return textures[name];
    }
    else
    {

        delete texture;
        return NULL;
    }

}

TextureManager::~TextureManager()
{

    
    sf::Texture* texture;
    map<string, sf::Texture*>::iterator iter = textures.begin();
    while (iter != textures.end())
    {
        texture = iter->second;
        delete texture;
        iter++;
    }

}