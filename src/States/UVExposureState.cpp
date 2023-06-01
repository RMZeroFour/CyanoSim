#include "states/State.h"
#include "Colors.h"

void UVExposureState::setLampTex()
{
	std::shared_ptr<sf::Image> uv = lampOn
		? Sim.GetResources().UVLampOn
		: Sim.GetResources().UVLampOff;
	LoadTexture(uvLamp, uv.get());
}

void UVExposureState::init()
{
	setLampTex();
	uvLampSpr.setPosition(WIDTH - uvLamp.getSize().x, 0);
	uvLampSpr.setTexture(uvLamp);

	compositeTex.create(200, 200);

	LoadTexture(paintedSheet, Sim.GetResources().PaintedSheet.get());
	LoadTexture(glassPane, Sim.GetResources().GlassPane.get());
	LoadTexture(woodenBoard, Sim.GetResources().WoodenBoard.get());

	std::shared_ptr<sf::Image> selected = Sim.GetResources().SelectedImage;
	sf::Image invSelected;
	invSelected.create(selected->getSize().x, selected->getSize().y);
	for (size_t i = 0; i < invSelected.getSize().x; i++)
	{
		for (size_t j = 0; j < invSelected.getSize().y; j++)
		{
			RGB original = selected->getPixel(i, j);
			byte b = (original.R + original.G + original.B) / 3;
			RGB inverted = RGB(255 - b, 255 - b, 255 - b);
			invSelected.setPixel(i, j, inverted);
		}
	}
	invertedTex.create(selected->getSize().x, selected->getSize().y);
	invertedTex.update(invSelected);
}

void UVExposureState::process(sf::Event& e)
{ }

void UVExposureState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({WIDTH, HEIGHT});
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("UV Exposure", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, sf::Color::White);
	ImGui::SetNextWindowPos(ImGui::GetStyle().ItemSpacing);
	ImGui::SetNextWindowSize({470, 80});
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color(65, 76, 96));
	ImGui::TextWrapped("Step 4) Place the wooden board, painted sheet, image negative and glass pane in order.");
	ImGui::TextWrapped("Then turn on the UV lamp for 10 minutes to develop it.");
	ImGui::PopStyleColor();
	ImGui::End();
	ImGui::PopStyleColor();

	ImGui::SetNextWindowBgAlpha(0);
	ImGui::SetNextWindowPos({10, 140});
	ImGui::SetNextWindowSize({265, 265});
	ImGui::Begin("Grid", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::BeginTable("Grid", 2);

	ImGui::TableNextColumn();
	if (progress < 2)
	{
		if (ImGui::ImageButton(paintedSheet, {100, 100}, 10))
		{
			if (progress == 1)
			{
				progress++;

				sf::Sprite spr(paintedSheet);
				spr.setScale(150.0f / paintedSheet.getSize().x, 150.0f / paintedSheet.getSize().y);
				spr.setPosition(100.0f - 150.0f / 2, 100.0f - 150.0f / 2);
				spr.setColor(sf::Color(255, 255, 255, 255));
				compositeTex.draw(spr);
				compositeTex.display();
			}
		}
	}

	ImGui::TableNextColumn();
	if (progress < 4)
	{
		if (ImGui::ImageButton(glassPane, {100, 100}, 10))
		{
			if (progress == 3)
			{
				progress++;

				sf::Sprite spr(glassPane);
				spr.setScale(200.0f / glassPane.getSize().x, 200.0f / glassPane.getSize().y);
				compositeTex.draw(spr);
				compositeTex.display();
			}
		}
	}

	ImGui::TableNextColumn();
	if (progress < 1)
	{
		if (ImGui::ImageButton(woodenBoard, {100, 100}, 10))
		{
			if (progress == 0)
			{
				progress++;

				sf::Sprite spr(woodenBoard);
				spr.setScale(200.0f / woodenBoard.getSize().x, 200.0f / woodenBoard.getSize().y);
				compositeTex.draw(spr);
				compositeTex.display();
			}
		}
	}

	ImGui::TableNextColumn();
	if (progress < 3)
	{
		if (ImGui::ImageButton(invertedTex, {100, 100}, 10))
		{
			if (progress == 2)
			{
				progress++;

				sf::Sprite spr(invertedTex);
				spr.setScale(150.0f / invertedTex.getSize().x, 150.0f / invertedTex.getSize().y);
				spr.setPosition(100.0f - 150.0f / 2, 100.0f - 150.0f / 2);
				spr.setColor(sf::Color(255, 255, 255, 125));
				compositeTex.draw(spr);
				compositeTex.display();
			}
		}
	}

	ImGui::EndTable();
	ImGui::End();

	sf::Sprite compositeSpr(compositeTex.getTexture());
	compositeSpr.setPosition(350, HEIGHT / 2 - 100);
	window.draw(compositeSpr);

	sf::Sprite lampSpr(uvLamp);
	lampSpr.setPosition(WIDTH - uvLamp.getSize().x, 0);
	window.draw(lampSpr);

	if (progress == 4)
	{
		if (!lampOn)
		{
			ImGui::SetCursorPos(ImVec2(WIDTH - 120, 0));
			if (ImGui::InvisibleButton("Lamp", {120, 120}))
			{
				lampOn = true;
				setLampTex();

				exposureClock.restart();
			}
		}
		else
		{
			if (timeElapsed < 5)
				timeElapsed = exposureClock.getElapsedTime().asSeconds();
			else
				doneExposure = true;

			ImGui::PushFont(Sim.GetResources().LargeFont);
			ImGui::SetCursorPos(ImVec2(375, HEIGHT / 2 + 110));
			ImGui::Text("%d / 10 minutes", (int)std::floor(timeElapsed * 2));
			ImGui::PopFont();
		}
	}

	if (doneExposure)
	{
		if (lampOn)
		{
			lampOn = false;
			setLampTex();
		}

		ImGui::SetCursorPos({WIDTH - 90, HEIGHT - 50});
		if (ImGui::Button("Next", {80, 40}))
		{
			auto ibs = std::make_unique<ImageBathState>(Sim);
			Sim.PushState(std::move(ibs));
		}
	}

	ImGui::End();
}