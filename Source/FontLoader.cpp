#include "FontLoader.h"

FontLoader::FontLoader(std::string const& dir)
{
    bool error = false;

    std::string base_dir = dir + "fonts/";

    if(!m_font_fuegoFatuo.loadFromFile(base_dir+"FuegoFatuo.ttf"))
        error = true;

    if(!m_font_upheavtt.loadFromFile(base_dir+"upheavtt.ttf"))
        error = true;

    if(error)
    {
        std::cerr << "error while charging fonts" << std::endl;
        throw std::exception();
    }
}

sf::Font & FontLoader::FuegoFatuo()
{
    return m_font_fuegoFatuo;
}

sf::Font & FontLoader::upheavtt()
{
    return m_font_upheavtt;
}
