#pragma once

#include <iostream>
#include <stack>
#include <memory>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"

enum class StateId { gameState, count };

class StateManager
{
public:
	sf::View camera;

	virtual ~StateManager();
	virtual void run();
	virtual void update(const float deltaTime, const sf::Event& e);
	virtual void draw();
	static const sf::Event eventHandler();
	static void addState(const StateId stateId);
	static bool removeState();
private:
	static std::stack<std::unique_ptr<StateManager>> states;

	static void checkState();
};
