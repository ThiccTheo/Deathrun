#pragma once

#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Tile : public Entity
{
public:
	static std::vector<Tile> tiles;

	Tile(const sf::Vector2i& indices);
	~Tile() override;
	static void update(const float deltaTime);
	static void draw();
private:
	static sf::VertexArray vertexArray;
};

