#include <iostream>

#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"
#include "Scene/Scene.hpp"

int main()
{
	if (ResourceManager::load())
	{
		srand(static_cast<unsigned int>(time(NULL)));
		Scene::init();
		StateManager::addState(StateId::gameState);
		ImGui::SFML::Shutdown(Scene::window);
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}