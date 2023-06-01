#include "states/State.h"
#include <iostream>
#include "Cyanotype.h"

void LoadSprite(sf::Sprite& spr, sf::Texture& tex, sf::Vector2f pos, sf::Vector2f size)
{
	spr.setTexture(tex);
	spr.setScale(size.x / tex.getSize().x, size.y / tex.getSize().y);
	spr.setPosition(pos.x, pos.y);
}

void ImageBathState::init()
{
	sf::Image* selected = Sim.GetResources().SelectedImage.get();
	sf::Image* oldPaper = Sim.GetResources().OldPaper.get();
	sf::Image* paintedSheet = Sim.GetResources().PaintedSheet.get();

	Sim.GetResources().ResultImage = createCyanotype(selected, oldPaper, paintedSheet);
	std::shared_ptr<sf::Image> cyanotypeImg = Sim.GetResources().ResultImage;
	LoadTexture(cyanotype, cyanotypeImg.get());

	std::shared_ptr<sf::Image> lighterImg = std::make_shared<sf::Image>();
	lighterImg->create(cyanotypeImg->getSize().x, cyanotypeImg->getSize().y);
	for (size_t i = 0; i < lighterImg->getSize().x; i++)
	{
		for (size_t j = 0; j < lighterImg->getSize().y; j++)
		{
			RGB pixel = cyanotypeImg->getPixel(i, j);

			HSL hsl = RGBToHSL(pixel);
			hsl.S = std::clamp(hsl.S * 0.80f, 0.0f, 1.0f);
			hsl.L = std::clamp(hsl.L * 1.25f, 0.0f, 1.0f);
			pixel = HSLToRGB(hsl);

			lighterImg->setPixel(i, j, pixel);
		}
	}
	LoadTexture(lightCyanotype, lighterImg.get());
	LoadSprite(currentlyHolding, lightCyanotype, {100, 120}, {100, 100});

	LoadTexture(waterTex, Sim.GetResources().WaterBucket.get());
	LoadSprite(waterTub, waterTex, {20, 250}, {150, 100});

	LoadTexture(peroxideTex, Sim.GetResources().PeroxideBucket.get());
	LoadSprite(peroxideTub, peroxideTex, {200, 250}, {150, 100});

	LoadTexture(rackTex, Sim.GetResources().DryingRack.get());
	LoadSprite(dryingRack, rackTex, {450, 150}, {150, 150});
}

void ImageBathState::process(sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(Sim.GetWindow());
			if (currentlyHolding.getGlobalBounds().contains(pos.x, pos.y))
			{
				dragging = true;
			}

			if (dragging)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(Sim.GetWindow());
				currentlyHolding.setPosition(sf::Vector2f(pos.x - 50, pos.y - 50));
			}
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (dragging)
		{
			dragging = false;
			sf::Vector2i pos = sf::Mouse::getPosition(Sim.GetWindow());

			if (progress == 0 || progress == 2)
			{
				if (waterTub.getGlobalBounds().contains(pos.x, pos.y))
				{
					progress++;
				}
			}
			else if (progress == 1)
			{
				if (peroxideTub.getGlobalBounds().contains(pos.x, pos.y))
				{
					progress++;
					currentlyHolding.setTexture(cyanotype);
				}
			}
			else if (progress == 3)
			{
				if (dryingRack.getGlobalBounds().contains(pos.x, pos.y))
				{
					progress++;
					currentlyHolding.setPosition(dryingRack.getPosition() + sf::Vector2f(25, 60));
					return;
				}
			}

			currentlyHolding.setPosition(sf::Vector2f(WIDTH / 5.0f - 50, HEIGHT / 3.0f - 50));
		}
	}
}

void ImageBathState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({WIDTH, HEIGHT});
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Image Bath", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, sf::Color::White);
	ImGui::SetNextWindowPos(ImGui::GetStyle().ItemSpacing);
	ImGui::SetNextWindowSize({540, 80});
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color(65, 76, 96));
	ImGui::TextWrapped("Step 5) Wash the cyanotype in water, then dip it in hydrogen peroxide, and finally wash once more in water.*");
	ImGui::TextWrapped("Then hang it on the drying rack to finish.");
	ImGui::PopStyleColor();
	ImGui::End();
	ImGui::PopStyleColor();

	window.draw(waterTub);
	window.draw(peroxideTub);
	window.draw(dryingRack);

	ImGui::SetCursorPos({70, 360});
	if (progress == 0 || progress == 2)
	{
		sf::RectangleShape rect({50, 5});
		rect.setPosition({70, 380});
		rect.setFillColor(sf::Color::Yellow);
		window.draw(rect);
	}
	ImGui::Text("Water");

	ImGui::SetCursorPos({200, 360});
	if (progress == 1)
	{
		sf::RectangleShape rect({160, 5});
		rect.setPosition({200, 380});
		rect.setFillColor(sf::Color::Yellow);
		window.draw(rect);
	}
	ImGui::Text("Hydrogen Peroxide");

	if (progress == 4)
	{
		ImGui::SetCursorPos({WIDTH - 90, HEIGHT - 50});
		if (ImGui::Button("Next", {80, 40}))
		{
			auto frs = std::make_unique<FinalResultState>(Sim);
			Sim.PushState(std::move(frs));
		}
	}

	window.draw(currentlyHolding);

	ImGui::SetCursorPos({10, HEIGHT - 50});
	ImGui::Text("* Colors of chemicals are not accurate,\nonly used to make the simulation look better!");

	ImGui::End();
}