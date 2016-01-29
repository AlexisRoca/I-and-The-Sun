#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>

class FontLoader
{
    public: 
        FontLoader(std::string const& dir);

        sf::Font & FuegoFatuo();
        sf::Font & upheavtt();

    private:
        sf::Font m_font_fuegoFatuo;
        sf::Font m_font_upheavtt;
};
