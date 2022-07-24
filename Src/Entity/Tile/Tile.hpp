#pragma once

#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

enum class TileType { none, grass, dirt, count };

class Tile : public Entity
{
public:
	static std::vector<Tile> tiles;

	Tile(const sf::Vector2i& indices, const TileType type);
	~Tile() override;
	static void update(const float deltaTime);
	static void draw();
private:
	static sf::VertexArray vertexArray;
	TileType type;
};

