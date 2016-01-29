#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class TextureLoader
{
private:
	sf::Texture * m_objectsTexture;
	sf::Texture * m_floorTexture;
	sf::Texture * m_characterTexture;
    sf::Texture * m_fireDetectorTexture;
	sf::Texture * m_teleporterTexture;
    sf::Texture * m_fireTexture;

public:
	TextureLoader(std::string const & url);
	virtual ~TextureLoader();

	sf::Texture * getFloorTexture() const;
	sf::Texture * getObjectsTexture() const;
	sf::Texture * getCharacterTexture() const;
    sf::Texture * getFireSensorTexture() const;
    sf::Texture * getFireTexture() const;
	sf::Texture const* getTeleporterTexture() const;
	void loadTexture(std::string const & url);
};

