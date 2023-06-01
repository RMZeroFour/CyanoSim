#pragma once
#include "imgui.h"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "../Simulator.h"

#define WIDTH 640
#define HEIGHT 480

class State
{
protected:
	Simulator& Sim;
	void CenteredText(const std::string& text);
	void CenteredImage(const sf::Texture& tex, sf::Vector2f size);
	void LoadTexture(sf::Texture& tex, sf::Image* imgPtr);

public:
	State(Simulator& s) : Sim(s) { }

	virtual void init() = 0;
	virtual void process(sf::Event& e) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

class MainMenuState : public State
{
public:
	MainMenuState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class SelectPictureState : public State
{
private:
	sf::Texture tex;

public:
	SelectPictureState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class MixSolutionsState : public State
{
private:
	sf::Texture pfcTexture;
	sf::Texture facTexture;
	sf::Texture beakerTexture;

	sf::Color mixColor;
	int fac = 0, pfc = 0;
	bool done = false;

public:
	MixSolutionsState(Simulator& s) 
		: State(s), mixColor(245, 220, 120)
	{ }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class PaintSheetState : public State
{
private:
	sf::Color sheetColor;
	sf::Color solnColor;

	sf::Vector2f displayPos, displaySize;

	sf::Texture paintbrush;
	sf::Texture strokeTex;

	sf::RenderTexture sheet;
	sf::Image result;

	bool allowNext = false;

public:
	PaintSheetState(Simulator& s)
		: State(s), sheetColor(255, 250, 240), solnColor(245, 220, 120)
	{ }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class UVExposureState : public State
{
private:
	sf::Texture paintedSheet;
	sf::Texture glassPane, woodenBoard;
	sf::Texture invertedTex;

	sf::Texture uvLamp;
	sf::Sprite uvLampSpr;

	sf::RenderTexture compositeTex;
	sf::Clock exposureClock;
	float timeElapsed = 0;
	bool doneExposure = false;

	bool lampOn = false;
	int progress = 0;

public:
	UVExposureState(Simulator& s) 
		: State(s)
	{ }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;

private:
	void setLampTex();
};

class ImageBathState : public State
{
private:
	sf::Sprite currentlyHolding;
	sf::Sprite waterTub;
	sf::Sprite peroxideTub;
	sf::Sprite dryingRack;

	sf::Texture waterTex;
	sf::Texture peroxideTex;
	sf::Texture rackTex;

	sf::Texture cyanotype;
	sf::Texture lightCyanotype;
	
	bool dragging = false;
	int progress = 0;
	bool allowNext = false;

public:
	ImageBathState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class FinalResultState : public State
{
private:
	sf::Texture resultTex;

public:
	FinalResultState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class RunToEndState : public State
{
public:
	RunToEndState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};

class AboutInfoState : public State
{
public:
	AboutInfoState(Simulator& s) : State(s) { }

	void init() override;
	void process(sf::Event& e) override;
	void draw(sf::RenderWindow& window) override;
};