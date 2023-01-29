#include "State.h"
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

void PaintSheetState::init()
{
	sheet.create(1024, 768);
	sheet.clear(sheetColor);

	displayPos = { 10, 75 };
	displaySize = { 620, 300 };

	std::shared_ptr<sf::Image> stroke = Sim.GetResources().BrushStroke;
	LoadTexture(strokeTex, stroke.get());

	std::shared_ptr<sf::Image> brush = Sim.GetResources().Paintbrush;
	LoadTexture(paintbrush, brush.get());
}

void PaintSheetState::process(sf::Event& e)
{ 
	if (e.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			allowNext = true;

			sf::Vector2i pos = sf::Mouse::getPosition(Sim.GetWindow());

			sf::Sprite stroke(strokeTex);
			stroke.setPosition(
				((pos.x - displayPos.x) * sheet.getSize().x / displaySize.x) - strokeTex.getSize().x / 2,
				((pos.y - displayPos.y) * sheet.getSize().y / displaySize.y) - strokeTex.getSize().y / 2);
			stroke.setColor(solnColor);

			sheet.draw(stroke);
			sheet.display();
		}
	}
}

void PaintSheetState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Paint Sheet", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, sf::Color::White);
	ImGui::SetNextWindowPos(ImGui::GetStyle().ItemSpacing);
	ImGui::SetNextWindowSize({ ImGui::GetContentRegionAvail().x, 40 });
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color(65, 76, 96));
	ImGui::TextWrapped("Step 3) Apply the mixture to the sheet of paper.");
	ImGui::PopStyleColor();
	ImGui::End();
	ImGui::PopStyleColor();

	sf::Sprite sheetSpr(sheet.getTexture());
	sheetSpr.setPosition(displayPos);
	sheetSpr.setScale(displaySize.x / sheet.getSize().x, displaySize.y / sheet.getSize().y);
	window.draw(sheetSpr);

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if ((mousePos.x >= displayPos.x && mousePos.x < displayPos.x + displaySize.x) &&
		(mousePos.y >= displayPos.y && mousePos.y < displayPos.y + displaySize.y))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		sf::Sprite brushSpr(paintbrush);
		brushSpr.setPosition(mousePos.x - 50, mousePos.y - paintbrush.getSize().y / 2);
		window.draw(brushSpr);
	}
	else
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}

	ImGui::SetCursorPos({ 10, HEIGHT - 50 });
	if (ImGui::Button("Fill", { 80, 40 }))
	{
		allowNext = true;
		sheet.clear(solnColor);
		sheet.display();
	}

	ImGui::SetCursorPos({ WIDTH / 2 - 40, HEIGHT - 50 });
	if (ImGui::Button("Reset", { 80, 40 }))
	{
		allowNext = false;
		sheet.clear(sheetColor);
		sheet.display();
	}

	ImGui::SetCursorPos({ WIDTH - 90, HEIGHT - 50 });
	if (allowNext && ImGui::Button("Next", { 80, 40 }))
	{
		result = sheet.getTexture().copyToImage();
		Sim.GetResources().PaintedSheet = std::make_unique<sf::Image>(result);

		auto uve = std::make_unique<UVExposureState>(Sim);
		Sim.PushState(std::move(uve));
	}

	ImGui::End();
}