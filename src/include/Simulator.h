#pragma once
#include <memory>
#include <stack>
#include "Resources.h"
#include <SFML/Graphics/RenderWindow.hpp>

class State;

class Simulator
{
public:
    Simulator();
    ~Simulator();

    void PushState(std::unique_ptr<State> state);
    void PopState();
    void SetState(std::unique_ptr<State> state);

    bool& IsSimulating();
    State* CurrentState();
    sf::RenderWindow& GetWindow();
    Resources& GetResources();

    void Run();

private:
    bool simulating;
    Resources resx;
    sf::RenderWindow window;
    std::stack<std::unique_ptr<State>> states;
};