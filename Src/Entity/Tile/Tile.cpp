#include "Tile.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"

std::vector<Tile> Tile::tiles;
sf::VertexArray Tile::vertexArray;

Tile::Tile(const sf::Vector2i& indices)
	: Entity(indices, sf::Vector2f(16.f, 16.f)) {}

Tile::~Tile() = default;

void Tile::update(const float deltaTime)
{
}

void Tile::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(tiles.size() * 4);

	int vertexPtr{ 0 };

	for (Tile& tile : tiles)
	{
		tile.transform = tile.body.getTransform();
		sf::Vertex* quad{ &vertexArray[vertexPtr] };

		for (int i{ 0 }; i < 4; i++)
		{
			tile.mesh[i] = tile.body.getPoint(i);
			quad[i] = tile.transform.transformPoint(tile.mesh[i]);
			quad[i].texCoords = tile.mesh[i];
		}

		vertexPtr += 4;
	}

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::tile]);
}
