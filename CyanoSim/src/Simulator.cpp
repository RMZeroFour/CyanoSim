#include "Simulator.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "escapi/escapi.h"
#include "States/State.h"

Simulator::Simulator()
    : window(sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Cyanotype Simulator", sf::Style::Titlebar | sf::Style::Close))
{
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    setupESCAPI();
    
    ImGui::GetIO().IniFilename = NULL;

    resx.LoadAssets();

    auto menu = std::make_unique<MainMenuState>(*this);
    PushState(std::move(menu));
}

Simulator::~Simulator()
{
    while (!states.empty())
        states.pop();

    ImGui::SFML::Shutdown();
}

void Simulator::PushState(std::unique_ptr<State> state)
{
    state->init();
    states.push(std::move(state));
}

void Simulator::PopState()
{
    states.pop();
}

void Simulator::SetState(std::unique_ptr<State> state)
{
    while (!states.empty())
        states.pop();

    state->init();
    states.push(std::move(state));
}

bool& Simulator::IsSimulating()
{
    return simulating;
}

State* Simulator::CurrentState()
{
    return states.top().get();
}

sf::RenderWindow& Simulator::GetWindow()
{
    return window;
}

Resources& Simulator::GetResources()
{
    return resx;
}

void Simulator::Run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        State* current = CurrentState();

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            current->process(event);
        }

        ImGui::SFML::Update(window, clock.restart());

        window.clear(sf::Color(137, 189, 214));

        ImGui::PushStyleColor(ImGuiCol_Button, sf::Color(65, 76, 96));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color(53, 61, 77));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, sf::Color(35, 41, 51));
        
        current->draw(window);
        
        ImGui::PopStyleColor(3);

        ImGui::SFML::Render(window);
        window.display();
    }
}
