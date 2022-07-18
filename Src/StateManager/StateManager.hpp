#pragma once

#include <iostream>
#include <stack>
#include <memory>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"

enum class StateType { gameState, menuState, settingsState, count };

class StateManager
{
public:
	sf::View camera;
	bool isPopped;

	virtual ~StateManager();
	virtual void run();
	virtual void update(const float deltaTime, const sf::Event& e);
	virtual void draw();
	static const sf::Event eventHandler();
	static void addState(const StateType stateType);
	static bool removeState();
private:
	static std::stack<std::unique_ptr<StateManager>> states;

	static void checkState();
};

