#pragma once

#include <iostream>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class TextureId { player, tile, count };
enum class ImageId { cursor, level, count };
enum class SoundBufferId { count };
enum class FontId { count };

class ResourceManager
{
public:
	static std::unordered_map<TextureId, sf::Texture> textureMap;
	static std::unordered_map<ImageId, sf::Image> imageMap;
	static std::unordered_map<SoundBufferId, sf::SoundBuffer> soundBufferMap;
	static std::unordered_map<FontId, sf::Font> fontMap;

	static const bool load();
};

