#pragma once
#include "Colors.h"
#include <memory>
#include <SFML/Graphics/Image.hpp>

RGB grayscale(RGB in);

RGB cyanotype(RGB in);

RGB divide(RGB over, RGB under);

std::shared_ptr<sf::Image> createCyanotype(sf::Image* input, sf::Image* oldPaper, sf::Image* mask = nullptr);