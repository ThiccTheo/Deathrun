#pragma once

#include <iostream>

#include "CommonImGui.hpp"
#include "CommonSFML.hpp"
#include "../StateManager.hpp"

class SettingsState : public StateManager
{
public:
	SettingsState();
	~SettingsState() override;
	void run() override;
	void update(const float deltaTime, const sf::Event& e) override;
	void draw() override;
};

