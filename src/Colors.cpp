#include "Colors.h"

HSL RGBToHSL(RGB rgb)
{
	HSL hsl = HSL(0, 0, 0);

	float r = (rgb.R / 255.0f);
	float g = (rgb.G / 255.0f);
	float b = (rgb.B / 255.0f);

	float min = std::fmin(std::fmin(r, g), b);
	float max = std::fmax(std::fmax(r, g), b);
	float delta = max - min;

	hsl.L = (max + min) / 2;

	if (delta == 0)
	{
		hsl.H = 0;
		hsl.S = 0.0f;
	}
	else
	{
		hsl.S = (hsl.L <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

		float hue;

		if (r == max)
		{
			hue = ((g - b) / 6) / delta;
		}
		else if (g == max)
		{
			hue = (1.0f / 3) + ((b - r) / 6) / delta;
		}
		else
		{
			hue = (2.0f / 3) + ((r - g) / 6) / delta;
		}

		if (hue < 0)
			hue += 1;
		if (hue > 1)
			hue -= 1;

		hsl.H = (int)(hue * 360);
	}

	return hsl;
}

RGB HSLToRGB(HSL hsl)
{
	auto HueToRGB = [](float v1, float v2, float vH)
	{
		if (vH < 0)
			vH += 1;

		if (vH > 1)
			vH -= 1;

		if ((6 * vH) < 1)
			return (v1 + (v2 - v1) * 6 * vH);

		if ((2 * vH) < 1)
			return v2;

		if ((3 * vH) < 2)
			return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

		return v1;
	};

	byte r = 0;
	byte g = 0;
	byte b = 0;

	if (hsl.S == 0)
	{
		r = g = b = (byte)(hsl.L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)hsl.H / 360;

		v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
		v1 = 2 * hsl.L - v2;

		r = (byte)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		g = (byte)(255 * HueToRGB(v1, v2, hue));
		b = (byte)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
	}

	return RGB(r, g, b);
}
