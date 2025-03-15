#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    static TextureManager& GetInstance() {
        static TextureManager instance;
        return instance;
    }

    const sf::Texture& GetTexture(const std::string& filepath) {
        auto it = mTextures.find(filepath);
        if (it != mTextures.end()) {
            return it->second;
        }

        sf::Texture& texture = mTextures[filepath]; // Création dans la map
        if (!texture.loadFromFile(filepath)) {
            std::cerr << "Error loading texture: " << filepath << std::endl;
            exit(EXIT_FAILURE);
        }

        return texture;
    }
    void Clear() {
        mTextures.clear();
    }

private:
    std::unordered_map<std::string, sf::Texture> mTextures;


    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
};

