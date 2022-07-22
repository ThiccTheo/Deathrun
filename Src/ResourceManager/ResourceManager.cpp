#include "ResourceManager.hpp"

std::unordered_map<TextureId, sf::Texture> ResourceManager::textureMap;
std::unordered_map<ImageId, sf::Image> ResourceManager::imageMap;
std::unordered_map<SoundBufferId, sf::SoundBuffer> ResourceManager::soundBufferMap;
std::unordered_map<FontId, sf::Font> ResourceManager::fontMap;

const bool ResourceManager::load()
{
	return
		textureMap[TextureId::player].loadFromFile("Data/Textures/Player.png") &&
		textureMap[TextureId::tile].loadFromFile("Data/Textures/Tile.png") &&

		imageMap[ImageId::cursor].loadFromFile("Data/Images/Cursor.png") &&
		imageMap[ImageId::level].loadFromFile("Data/Images/Level.png");
}
