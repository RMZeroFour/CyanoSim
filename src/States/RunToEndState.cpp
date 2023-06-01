#include "states/State.h"
#include <cmath>
#include "Colors.h"
#include "Cyanotype.h"

void RunToEndState::init()
{ }

void RunToEndState::process(sf::Event& e)
{ }

void RunToEndState::draw(sf::RenderWindow& window)
{
    sf::Image* selected = Sim.GetResources().SelectedImage.get();
    sf::Image* oldPaper = Sim.GetResources().OldPaper.get();
    Sim.GetResources().ResultImage = createCyanotype(selected, oldPaper);

    auto frs = std::make_unique<FinalResultState>(Sim);
    Sim.PushState(std::move(frs));
}