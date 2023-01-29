#include "Cyanotype.h"
#include <cmath>

RGB grayscale(RGB in)
{
    byte b = (std::min(in.R, std::min(in.G, in.B)) + std::max(in.R, std::max(in.G, in.B))) / 2;
    return { b, b, b };
}

RGB cyanotype(RGB in)
{
    HSL hsl = RGBToHSL(in);
    hsl.H = (hsl.H - 180) + 25;
    hsl.S = 0.25f;
    return HSLToRGB(hsl);
}

RGB divide(RGB over, RGB under)
{
    byte nr = std::clamp((int)(256.0f / ((float)over.R / under.R)), 0, 255);
    byte ng = std::clamp((int)(256.0f / ((float)over.G / under.G)), 0, 255);
    byte nb = std::clamp((int)(256.0f / ((float)over.B / under.B)), 0, 255);
    return sf::Color(nr, ng, nb);
}

std::shared_ptr<sf::Image> createCyanotype(sf::Image* input, sf::Image* oldPaper, sf::Image* mask)
{
    std::shared_ptr<sf::Image> img = std::make_shared<sf::Image>();
    img->create(input->getSize().x, input->getSize().y);

    for (size_t i = 0; i < img->getSize().x; i++)
    {
        for (size_t j = 0; j < img->getSize().y; j++)
        {
            RGB pixel = input->getPixel(i, j);

            bool process = true;

            if (mask)
            {
                int nx = (int)((float)i / img->getSize().x * mask->getSize().x);
                int ny = (int)((float)j / img->getSize().y * mask->getSize().y);
                RGB maskPixel = mask->getPixel(nx, ny);
                process = !(maskPixel.R == 255 && maskPixel.G == 250 && maskPixel.B == 240);
            }

            if(process)
            {
                pixel = grayscale(pixel);
                pixel = cyanotype(pixel);

                int nx = (int)((float)i / img->getSize().x * oldPaper->getSize().x);
                int ny = (int)((float)j / img->getSize().y * oldPaper->getSize().y);
                RGB sampled = oldPaper->getPixel(nx, ny);
                pixel = divide(sampled, pixel);
            }
            else
            {
                pixel = RGB(255, 250, 240);
            }

            img->setPixel(i, j, pixel);
        }
    }

    return img;
}
