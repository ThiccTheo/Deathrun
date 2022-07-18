#pragma once

#include <iostream>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"
#include "../StateManager.hpp"

class MenuState : public StateManager
{
public:
	MenuState();
	~MenuState() override;
	void run() override;
	void update(const float deltaTime, const sf::Event& e) override;
	void draw() override;
};

