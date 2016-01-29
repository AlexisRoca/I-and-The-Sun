#include "Building.h"

Building::Building(TextureLoader const * textureLoader, unsigned int maxBurnedDamage, unsigned int currentBurnedDamage):
	m_maxBurnedDamage(maxBurnedDamage), 
	m_currentBurnedDamage(currentBurnedDamage),
	m_textureLoader(textureLoader),
	m_floors(std::vector<Floor *>())
{}

Building::~Building()
{
    for(auto it = m_floors.begin(); it != m_floors.end(); ++it)
        delete *it;
}

std::vector<Floor * > * Building::getFloors()
{
	return &m_floors;
}

Floor * Building::getCurrentFloor()
{
	return m_currentFloor;
}


void Building::loadNextFloor()
{
	//unsigned int whichTeleport = m_currentFloor;

	//for (auto it = m_floors[whichTeleport]->getTeleporter().cbegin();
	//	it != m_floors[whichTeleport]->getTeleporter().cend(); ++it){
	//	if ((*it)->getStatusColision())
	//	{
	//		if ((*it)->getDirection() == 0) {
	//			if (m_currentFloor > 0) {
	//				m_currentFloor = 0;
	//			}
	//		}
	//		else
	//		{
	//			m_currentFloor = 1;
	//		}

	//	}
	//}
}

void Building::loadBuilding(std::string const &path)
{
	std::ifstream levelFile(path, std::ios_base::in);

	Floor * currentFloor = new Floor(m_textureLoader);

	//std::unordered_map<unsigned char, bool> fireDetectorsSentInRoom;

	bool mapConstruction = false;
	bool backgroundConstruction = false;

	unsigned int floorId = 0;
	
	while(levelFile.good())
	{
		std::string line;
		getline(levelFile, line);

		if(line.length() > 0)
		{
			if (line[0] == '=')
			{
				//new floor
				m_floors.push_back(currentFloor);
				currentFloor = new Floor(m_textureLoader);
				floorId++;
			}

			else if(line[0] == 'M')
			{
				mapConstruction = true;
			}

			else if(line[0] == 'B')
			{
				mapConstruction = false;
				backgroundConstruction = true;

				//the map of the floor is over
				//inspection to determine the different rooms
				for(unsigned int i = 0; i < currentFloor->getFloorMap().size(); ++i)
					for(unsigned int j = 0; j < currentFloor->getFloorMap()[i].size(); ++j)
						if((currentFloor->getFloorMap()[i][j] != '0') && (currentFloor->getFloorMap()[i][j] != 'P'))
						{
							bool alreadyDefine = false;
							for(auto it = currentFloor->getRooms()->cbegin(); it != currentFloor->getRooms()->cend(); ++it)
							{
								if(currentFloor->getFloorMap()[i][j] == it->second->getRoomId())
									alreadyDefine = true;
							}
						
							if(!alreadyDefine)
								currentFloor->addRoom(currentFloor->getFloorMap()[i][j]);
						}
			}

			else if(line[0] == '|')
			{
				backgroundConstruction = false;
			}

			else if (mapConstruction)
			{
				std::vector<unsigned char> buffer;
				for (auto it = line.cbegin(); it != line.cend(); ++it)
					buffer.push_back(*it);

				currentFloor->addLineToRoomsMap(buffer);
			}

			else if(backgroundConstruction)
			{
				std::vector<unsigned char> buffer;
				for (auto it = line.cbegin(); it != line.cend(); ++it)
					buffer.push_back(*it);

				currentFloor->addLineToBackground(buffer);
			}

			//Furniture
			else if (line[0] == 'f')
			{
				if(line.length() >= 6)
				{
					unsigned char objectID = line[1];
					unsigned char objectType = line[2];
					unsigned char roomId = line[3];

					std::string x_str;
					std::string y_str;
					bool first = true;

					for (unsigned int i = 4; i < line.length(); ++i)
					{
						if (line[i] == ':')
							first = false;
						else
							(first ? x_str : y_str).push_back(line[i]);
					}

					int x = atoi(x_str.c_str());
					int y = atoi(y_str.c_str());

					BurnableObject * obj = BurnableObject::fromID(objectType, x, y, m_textureLoader->getObjectsTexture(), m_textureLoader->getFireTexture());
					currentFloor->getRoom(roomId)->addFurniture(obj);
				}

				else
					std::cerr << "error while loading level '" << path << ": malformed object declaration" << std::endl;
			}

			//Fire Sensor
			else if (line[0] == 's')
			{
				if (line.length() >= 5)
				{
					unsigned char roomId = line[1];

					std::string x_str;
					std::string y_str;
					bool first = true;

					for (unsigned int i = 2; i < line.length(); ++i)
					{
						if (line[i] == ':')
							first = false;
						else
							(first ? x_str : y_str).push_back(line[i]);
					}

					unsigned int x = atoi(x_str.c_str());
					unsigned int y = atoi(y_str.c_str());

					FireSensor * fs = new FireSensor(x, y, 64, m_textureLoader->getFireSensorTexture());
					currentFloor->getRoom(roomId)->addFireSensor(fs);
				}

				else
					std::cerr << "error while loading level '" << path << " : malformed fire detector declaration" << std::endl;
			}

			//Doors
			else if (line[0] == 'd')
			{
				if (line.length() >= 4)
				{
					std::pair<unsigned char, unsigned char> adjacentRooms;
					adjacentRooms.first = line[1];
					adjacentRooms.second = line[2];

					std::string x_str;
					std::string y_str;
					bool posxDefinition = true;

					for (unsigned int i = 3; i < line.length(); ++i)
					{
						if (line[i] == ':')
							posxDefinition = false;
						else
							(posxDefinition ? x_str : y_str).push_back(line[i]);
					}

					unsigned int x = atoi(x_str.c_str());
					unsigned int y = atoi(y_str.c_str());

					Door * door = new Door(x, y, adjacentRooms, m_textureLoader->getObjectsTexture());
					currentFloor->addDoor(door);
				}
			}

			//else if (line[0] == 't')
			//{
			//	//teleporter
			//	if (line.length() >= 5)
			//	{
			//		std::string x_str;
			//		std::string y_str;
			//		unsigned char direction = line[1];

			//		bool first = true;

			//		for (unsigned int i = 2; i < line.length(); ++i)
			//		{
			//			if (line[i] == ':')
			//				first = false;

			//			else
			//				(first ? x_str : y_str).push_back(line[i]);
			//		}

			//		unsigned int x = atoi(x_str.c_str());
			//		unsigned int y = atoi(y_str.c_str());

			//		Teleporter * teleporter = new Teleporter(x * 32, y * 32, m_textureLoader->getTeleporterTexture(), direction);
			//		currentFloor->addTeleporter(teleporter);
			//	}
			//}
		}

		floorId++;
	}

	m_currentFloor = m_floors[0];

	////delete orphaned fireDetectors
	//for (auto it = fireDetectors.begin(); it != fireDetectors.end(); ++it)
	//	if (!fireDetectorsSentInRoom.at(it->first))
	//		delete it->second;
}

void Building::draw(sf::RenderWindow *window)
{
	m_currentFloor->draw(window);
	//this->drawHUD();
}

void Building::update(sf::Clock const & clk)
{
	m_currentFloor->update(clk);
}

bool Building::checkCollisions(Ray * collisionRay, unsigned char characterCurrentRoom)
{
    m_currentFloor->collision(collisionRay);
    return collisionRay->validIntersectionFound();
}
