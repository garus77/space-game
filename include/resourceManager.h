// resourceManager.h
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <unordered_map>

class ResourceManager
{
  public:
    // Fonts: resources/fonts/{id}.ttf
    const sf::Font &getFont(const std::string &id) { return getResource(id, fonts, "resources/fonts/", ".ttf"); }

    // Textures: resources/textures/{id}.png
    const sf::Texture &getTexture(const std::string &id) { return getResource(id, textures, "resources/textures/", ".png"); }

    // Audio: resources/audio/{id}.wav
    const sf::SoundBuffer &getSoundBuffer(const std::string &id) { return getResource(id, sounds, "resources/audio/", ".wav"); }

  private:
    // Generic loader: looks in `cache` first, otherwise loads basePath + id + ext
    template <typename R> const R &getResource(const std::string &id, std::unordered_map<std::string, R> &cache, const char *basePath, const char *ext)
    {
        auto it = cache.find(id);
        if (it != cache.end()) return it->second;

        R resource;
        if (!resource.loadFromFile(std::string(basePath) + id + ext)) throw std::runtime_error("ResourceManager: failed to load '" + id + "' from '" + basePath + id + ext + "'");

        auto inserted = cache.emplace(id, std::move(resource));
        return inserted.first->second;
    }

    // Cached fonts, owned by this manager
    std::unordered_map<std::string, sf::Font> fonts;
    // Cached textures, owned by this manager
    std::unordered_map<std::string, sf::Texture> textures;
    // Cached soundbuffers, owned by this manager
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};
