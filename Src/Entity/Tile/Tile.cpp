#include "Tile.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../../Tools/ScopedTimer/ScopedTimer.hpp"

std::vector<Tile> Tile::tiles;
sf::VertexArray Tile::vertexArray;

Tile::Tile(const sf::Vector2i& indices, const TileType type)
	: Entity{ indices, sizeMap[EntityType::tile] },
	type{ type }
{
}

Tile::~Tile() = default;

void Tile::update(const float deltaTime)
{
}

void Tile::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(tiles.size() * 4);

	int vertexPtr{};

	for (Tile& tile : tiles)
	{
		tile.transform = tile.body.getTransform();
		sf::Vertex* quad{ &vertexArray[vertexPtr] };

		for (int i{}; i < 4; ++i)
		{
			tile.mesh[i] = tile.body.getPoint(i);
			quad[i] = tile.transform.transformPoint(tile.mesh[i]);
			quad[i].texCoords = sf::Vector2f{ tile.mesh[i].x, tile.mesh[i].y};
		}

		vertexPtr += 4;
	}

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::tile]);
}
