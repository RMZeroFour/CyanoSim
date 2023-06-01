#include "states/State.h"

void State::CenteredText(const std::string& text)
{
	float offset = (ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(text.c_str()).x) / 2;
	ImGui::SetCursorPosX(offset);
	ImGui::Text(text.c_str());
}

void State::CenteredImage(const sf::Texture& tex, sf::Vector2f size)
{
	float offset = (ImGui::GetWindowWidth() - size.x) / 2;
	ImGui::SetCursorPosX(offset);
	ImGui::Image(tex, size);
}

void State::LoadTexture(sf::Texture& tex, sf::Image* imgPtr)
{
	tex.create(imgPtr->getSize().x, imgPtr->getSize().y);
	tex.update(*imgPtr);
}
