#include "TextureLoader.h"

#include <exception>

TextureLoader::TextureLoader(std::string const & url) :
	m_objectsTexture(new sf::Texture()),
	m_floorTexture(new sf::Texture()),
	m_characterTexture(new sf::Texture()),
    m_fireDetectorTexture(new sf::Texture()),
	m_teleporterTexture(new sf::Texture()),
    m_fireTexture(new sf::Texture())
{
	loadTexture(url+"sprites/");
}


TextureLoader::~TextureLoader()
{
	delete m_floorTexture;
	delete m_objectsTexture;
	delete m_characterTexture;
    delete m_fireDetectorTexture;
	delete m_teleporterTexture;
    delete m_fireTexture;
}

sf::Texture * TextureLoader::getFloorTexture() const 
{
	return m_floorTexture;
}

sf::Texture * TextureLoader::getObjectsTexture() const
{
	return m_objectsTexture;
}

sf::Texture * TextureLoader::getCharacterTexture() const 
{
	return m_characterTexture;
}

sf::Texture * TextureLoader::getFireSensorTexture() const
{
    return m_fireDetectorTexture;
}

sf::Texture const* TextureLoader::getTeleporterTexture() const
{
	return m_teleporterTexture;
}

sf::Texture * TextureLoader::getFireTexture() const
{
    return m_fireTexture;
}

//On passe l'url du dossier de Textures
void TextureLoader::loadTexture(std::string const & url)
{
	if(!m_floorTexture->loadFromFile((url + "floor/tileset.png").c_str()))
    {
		std::cerr << "Error when loading the texture of the floor" << std::endl;
        throw std::exception();
    }

	if(!m_objectsTexture->loadFromFile((url + "mobilier/tileset.png").c_str()))
    {
		std::cerr << "Error when loading the texture of the objects" << std::endl;
        throw std::exception();
    }
	
	if(!m_characterTexture->loadFromFile((url + "spooky/spooky-tileset-2.png").c_str()))
    {
		std::cerr << "Error when loading the texture of the character" << std::endl;
        throw std::exception();
    }

    if(!m_fireDetectorTexture->loadFromFile((url + "fireDetector/tileset.png").c_str()))
    {
        std::cerr << "Error when loading the texture of the fire detector" << std::endl;
        throw std::exception();
    }

	if(!m_teleporterTexture->loadFromFile((url + "mobilier/stair.png").c_str()))
	{
		std::cerr << "Error when loading the texture of the fire detector" << std::endl;
		throw std::exception();
	}

    if(!m_fireTexture->loadFromFile((url + "fire/tileset.png").c_str()))
    {
        std::cerr << "Error when loading the fire texture" << std::endl;
        throw std::exception();
    }
}
