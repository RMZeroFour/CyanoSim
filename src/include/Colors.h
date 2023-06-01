#pragma once
#include <cmath>
#include <SFML/Graphics/Color.hpp>

typedef unsigned char byte;

struct RGB
{
	byte R;
	byte G;
	byte B;

	RGB(byte r, byte g, byte b)
		: R(r), G(g), B(b)
	{ }

	RGB(sf::Color c)
		: R(c.r), G(c.g), B(c.b)
	{ }

	operator sf::Color () { return sf::Color(R, G, B); }
};

struct HSL
{
	int H;
	float S;
	float L;

	HSL(int h, float s, float l)
		: H(h), S(s), L(l)
	{ }
};

HSL RGBToHSL(RGB rgb);

RGB HSLToRGB(HSL hsl);