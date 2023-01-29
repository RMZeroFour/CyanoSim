#include "State.h"

void MainMenuState::init()
{
}

void MainMenuState::process(sf::Event& e)
{ }

void MainMenuState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushFont(Sim.GetResources().TitleFont);
	CenteredText("Cyanotype");
	CenteredText("Simulator");
	ImGui::PopFont();

	ImGui::Dummy({ 0, 75 });

	ImGui::PushFont(Sim.GetResources().LargeFont); 
	if (ImGui::Button("Begin Simulation", { -1.0f, 50.0f }))
	{
		Sim.IsSimulating() = true;

		auto sls = std::make_unique<SelectPictureState>(Sim);
		Sim.PushState(std::move(sls));
	}

	if (ImGui::Button("Run (Without Simulating)", { -1.0f, 50.0f }))
	{
		Sim.IsSimulating() = false;

		auto sls = std::make_unique<SelectPictureState>(Sim);
		Sim.PushState(std::move(sls));
	}

	if (ImGui::Button("About Cyanotypes", { -1.0f, 50.0f }))
	{
		auto ais = std::make_unique<AboutInfoState>(Sim);
		Sim.PushState(std::move(ais));
	}
	ImGui::PopFont();

	ImGui::SetCursorPos({ 0, HEIGHT - 60 });
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color::Black);
	CenteredText("Chemistry Internal Assessment 3");
	CenteredText("Ritobroto Mukherjee XI-A");
	ImGui::PopStyleColor();

	ImGui::End();
}