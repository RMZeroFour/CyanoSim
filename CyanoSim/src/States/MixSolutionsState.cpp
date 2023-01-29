#include "State.h"
#include <SFML/Graphics/Texture.hpp>

void MixSolutionsState::init()
{
	std::shared_ptr<sf::Image> pfc = Sim.GetResources().PFCBottle;
	pfcTexture.create(pfc->getSize().x, pfc->getSize().y);
	pfcTexture.update(*pfc);

	std::shared_ptr<sf::Image> fac = Sim.GetResources().FACBottle;
	facTexture.create(fac->getSize().x, fac->getSize().y);
	facTexture.update(*fac);

	std::shared_ptr<sf::Image> beaker = Sim.GetResources().EmptyBeaker;
	beakerTexture.create(beaker->getSize().x, beaker->getSize().y);
	beakerTexture.update(*beaker);
}

void MixSolutionsState::process(sf::Event & e)
{ }

void MixSolutionsState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin("Mix Solutions", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, sf::Color::White);
	ImGui::SetNextWindowPos(ImGui::GetStyle().ItemSpacing);
	ImGui::SetNextWindowSize({ ImGui::GetContentRegionAvail().x, 60 });
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color(65, 76, 96));
	ImGui::TextWrapped("Step 2) Mix 5 parts Ferric Ammonium Citrate with 4 parts Potassium Ferricyanide in the beaker.*");
	ImGui::PopStyleColor();
	ImGui::End();
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Button, sf::Color::Transparent);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Transparent);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, sf::Color::Transparent);

	ImGui::SetCursorPos({ 10, 125 });
	if(ImGui::ImageButton(pfcTexture))
	{
		if (pfc < 4)
			pfc++;
	}

	ImGui::SetCursorPos({ WIDTH/2 - 62.5f, 175 });
	ImGui::Image(beakerTexture);

	sf::RectangleShape rect({ 95, 10 });
	rect.setPosition({ WIDTH / 2 - 62.5f + 15, 325 - (pfc + fac + 1) * rect.getSize().y });
	for (size_t i = 0; i < pfc + fac; i++)
	{
		sf::Color fill = 
			(pfc == 0 && fac > 0) ? sf::Color(218, 179, 69) :
			(fac == 0 && pfc > 0) ? sf::Color(233, 54, 39) :
			mixColor;

		rect.move(0, rect.getSize().y);
		rect.setFillColor(fill);
		window.draw(rect);
	}

	ImGui::PushFont(Sim.GetResources().LargeFont);
	ImGui::SetCursorPos({ WIDTH / 2 - 20, 340 });
	ImGui::Text("%d : %d", pfc, fac);
	ImGui::PopFont();

	ImGui::SetCursorPos({ WIDTH-110, 125 });
	if (ImGui::ImageButton(facTexture))
	{
		if (fac < 5)
			fac++;
	}

	ImGui::PopStyleColor(3);

	if (fac == 5 && pfc == 4 && !done)
	{
		done = true;
	}

	if (done)
	{
		ImGui::SetCursorPos({ WIDTH - 90, HEIGHT - 50 });
		if (ImGui::Button("Next", { 80, 40 }))
		{
			auto pss = std::make_unique<PaintSheetState>(Sim);
			Sim.PushState(std::move(pss));
		}
	}

	ImGui::SetCursorPos({ 10, HEIGHT - 50 });
	ImGui::Text("* Colors of chemicals are not accurate,\nonly used to make the simulation look better!");

	ImGui::End();
}