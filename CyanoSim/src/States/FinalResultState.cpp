#include "State.h"
#include <tinyfiledialogs.h>

void FinalResultState::init()
{
	std::shared_ptr<sf::Image> resultImg = Sim.GetResources().ResultImage;
	resultTex.create(resultImg->getSize().x, resultImg->getSize().y);
	resultTex.update(*resultImg);
}

void FinalResultState::process(sf::Event& e)
{ }

void FinalResultState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Final Result", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::Dummy({ 0, 20 });
	CenteredImage(resultTex, { WIDTH - 200, HEIGHT - 200 });
	ImGui::Dummy({ 0, 20 });

	ImGui::PushFont(Sim.GetResources().LargeFont);
	if (ImGui::Button("Save Result", { -1.0f, 50.0f }))
	{
		const char* filter[] = { "*.png" };
		const char* filepath = tinyfd_saveFileDialog("Save image", "", 1, filter, ".PNG file");

		if (filepath)
		{
			Sim.GetResources().ResultImage->saveToFile(filepath);
		}
	}

	if (ImGui::Button("Go Back", { -1.0f, 50.0f }))
	{
		auto mms = std::make_unique<MainMenuState>(Sim);
		Sim.SetState(std::move(mms));
	}
	ImGui::PopFont();
	
	ImGui::End();
}