#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>

class Resources
{
public:
	ImFont* TitleFont;
	ImFont* RegularFont;
	ImFont* LargeFont;

	std::shared_ptr<sf::Image> Flowers;
	
	std::shared_ptr<sf::Image> PFCBottle;
	std::shared_ptr<sf::Image> FACBottle;
	std::shared_ptr<sf::Image> EmptyBeaker;

	std::shared_ptr<sf::Image> Paintbrush;
	std::shared_ptr<sf::Image> BrushStroke;
	
	std::shared_ptr<sf::Image> UVLampOn;
	std::shared_ptr<sf::Image> UVLampOff;
	
	std::shared_ptr<sf::Image> GlassPane;
	std::shared_ptr<sf::Image> WoodenBoard;

	std::shared_ptr<sf::Image> OldPaper;

	std::shared_ptr<sf::Image> WaterBucket;
	std::shared_ptr<sf::Image> PeroxideBucket;
	
	std::shared_ptr<sf::Image> DryingRack;

	std::shared_ptr<sf::Image> SelectedImage;
	std::shared_ptr<sf::Image> PaintedSheet;
	std::shared_ptr<sf::Image> ResultImage;

public:
	void LoadAssets()
	{
		RegularFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets\\Montserrat-Regular.ttf", 20);
		LargeFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets\\Montserrat-SemiBold.ttf", 25);
		TitleFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets\\Montserrat-SemiBold.ttf", 40);
		ImGui::GetIO().FontDefault = RegularFont;
		ImGui::SFML::UpdateFontTexture();

		Flowers = std::make_shared<sf::Image>();
		Flowers->loadFromFile("assets\\flowers.png");

		PFCBottle= std::make_shared<sf::Image>();
		PFCBottle->loadFromFile("assets\\pfc bottle.png");
		FACBottle = std::make_shared<sf::Image>();
		FACBottle->loadFromFile("assets\\fac bottle.png");
		EmptyBeaker = std::make_shared<sf::Image>();
		EmptyBeaker->loadFromFile("assets\\empty beaker.png");

		Paintbrush = std::make_shared<sf::Image>();
		Paintbrush->loadFromFile("assets\\paintbrush.png");
		BrushStroke = std::make_shared<sf::Image>();
		BrushStroke->loadFromFile("assets\\brush stroke.png");

		UVLampOn = std::make_shared<sf::Image>();
		UVLampOn->loadFromFile("assets\\spotlight on.png");
		UVLampOff = std::make_shared<sf::Image>();
		UVLampOff->loadFromFile("assets\\spotlight off.png");

		GlassPane = std::make_shared<sf::Image>();
		GlassPane->loadFromFile("assets\\glass pane.png");
		WoodenBoard = std::make_shared<sf::Image>();
		WoodenBoard->loadFromFile("assets\\wooden board.png");

		OldPaper = std::make_shared<sf::Image>();
		OldPaper->loadFromFile("assets\\old paper.png");

		WaterBucket = std::make_shared<sf::Image>();
		WaterBucket->loadFromFile("assets\\water container.png");
		PeroxideBucket = std::make_shared<sf::Image>();
		PeroxideBucket->loadFromFile("assets\\h2o2 container.png");

		DryingRack = std::make_shared<sf::Image>();
		DryingRack->loadFromFile("assets\\drying rack.png");
	}
};