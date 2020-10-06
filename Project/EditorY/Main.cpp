#include "editor.h"
#include <SFML/Graphics.hpp>
#include <thread>

//const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
//const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
//const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
//const	char*	largeWorld	=	"../../worldmap/large_world.ybin";


Editor editor;
std::vector<sf::Sprite> sprites;
sf::RenderWindow* gameWindow = nullptr;
bool run = true;
bool update = false;

void tintTile(sf::Sprite *tile, CLIMATE clm) {
	switch (clm)
	{
	case SEA:
		tile->setColor(sf::Color::Blue);
		break;
	case CONTINENTAL:
		tile->setColor(sf::Color(64, 158, 64, 255));
		break;
	case OCEANIC:
		tile->setColor(sf::Color::Green);
		break;
	case MEDITERRAN:
		tile->setColor(sf::Color(158, 168, 0, 255));
		break;
	case TROPICAL:
		tile->setColor(sf::Color(20, 208, 20, 255));
		break;
	case ARID:
		tile->setColor(sf::Color(200, 100, 0, 255));
		break;
	case DESERT:
		tile->setColor(sf::Color::Yellow);
		break;
	case NORDIC:
		tile->setColor(sf::Color(0, 200, 200, 255));
		break;
	case POLAR:
		tile->setColor(sf::Color::White);
		break;
	default:
		break;
	}
}

void renderLoop() {
	int windowHeights = 1000;
	int windowWidth = 1600;
	sf::Event sfevent;
	sf::Texture tileTexture;
	tileTexture.loadFromFile("../../images/default.png");

	gameWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeights), "Game");
	while (run) {
		if (update) {
			WorldMap* wMap = editor.getROworldMap();
			if (wMap->sizeX * wMap->sizeY > 0) {

				if (sprites.size() > wMap->sizeX * wMap->sizeY) {
					sprites.clear();
				}
				sprites.reserve(wMap->sizeX * wMap->sizeY);


				for (int y = 0; y < wMap->sizeY; y++) {
					for (int x = 0; x < wMap->sizeX; x++) {
						CLIMATE tileClimate;
						sf::Sprite tileSprite = sf::Sprite(tileTexture);
						tileSprite.setPosition(x * 16, y * 16);
						tileSprite.setScale(0.5f, 0.5f);
						wMap->regions[x + y * wMap->sizeX].getRegionInfo(&tileClimate, nullptr, nullptr, nullptr, nullptr);
						tintTile(&tileSprite, tileClimate);
						//sprites[x + y * wMap.sizeX].setTexture(tileTexture);
						//sprites[x + y * wMap.sizeX].setPosition(x * 32, y * 32);
						if(x + y * wMap->sizeX >= sprites.size())
							sprites.push_back(tileSprite);
						else
							sprites[x + y * wMap->sizeX] = tileSprite;
					}
				}
			}
			update = false;
		}

		if(gameWindow->pollEvent(sfevent)){
			if (sfevent.type == sf::Event::Closed){
				gameWindow->close();
				run = false;
			}
		}


		gameWindow->clear();

		if(sprites.size() > 0)
			for (sf::Sprite &sprite : sprites) {
				gameWindow->draw(sprite);
			}

		gameWindow->display();
	}
	delete gameWindow;
}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::thread renderThread(renderLoop);
	

	std::string welcome = "Welcome to the editor, type \"help\" for commands";

	std::cout << welcome << std::endl;

	std::cout << std::endl << '>';
	while(update = editor.update()){	};


	run = false;
	renderThread.join();

	return 0;
}