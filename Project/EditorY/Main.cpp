#include "editor.h"
#include <SFML/Graphics.hpp>
#include <thread>

//const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
//const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
//const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
//const	char*	largeWorld	=	"../../worldmap/large_world.ybin";

static sf::Color tileTints[9]{	
		sf::Color(64,64,255, 255),	//SEA
		sf::Color(40,205,40, 255),	//CONTINENTAL
		sf::Color(64,205,205, 255), //OCEANIC
		sf::Color(140,190,120, 255),//MEDITERRAN
		sf::Color(0,255,0, 255), 	//TROPICAL
		sf::Color(240,190,50, 255),	//ARID
		sf::Color(205,205,0, 255),	//DESERT
		sf::Color(160,240,230, 255),//NORDIC
		sf::Color(210,230,240, 255),//POLAR
	};		
Editor editor;
std::vector<sf::Sprite> sprites;
std::vector<sf::Drawable*> uiElemnts;
sf::RenderWindow* gameWindow = nullptr;
bool run = true;
bool update = false;

void tintTile(sf::Sprite *tile, CLIMATE clm) {
	/*switch (clm)
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
	}*/
	tile->setColor(tileTints[(int)clm]);
}
void renderUI() {
	sf::View current = gameWindow->getView();
	sf::View defaultView = gameWindow->getDefaultView();
	gameWindow->setView(defaultView);
	for (sf::Drawable* element : uiElemnts) {
		gameWindow->draw(*element);
	}
	gameWindow->setView(current);
}

void moveView(float dirX, float dirY, float speed) {
	sf::View current = gameWindow->getView();
	current.move(dirX * speed, dirY * speed);
	gameWindow->setView(current);
}

void renderLoop() {
	int windowHeights = 1000;
	int windowWidth = 1600;
	sf::Event sfevent;
	sf::Texture tileTexture[2];
	tileTexture[0].loadFromFile("../../images/default.png");
	tileTexture[1].loadFromFile("../../images/spawn_plain.png");
	
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	sf::Text uitext;
	uitext.setFont(font);
	uitext.setString("test");
	uitext.setCharacterSize(14);
	uitext.setOutlineColor(sf::Color::Black);
	uitext.setOutlineThickness(1.5f);
	sf::Text* clmCountPtr[9];
	uint16_t clmCounts[9]{0};

	sf::Sprite uiSprite;
	uiSprite.setTexture(tileTexture[0]);
	uiSprite.setScale(0.5f, 0.5f);

	{
		sf::String clmStr[] { "SEA", "CONTINENTAL", "OCEANIC", "MEDITERRAN", "TROPICAL", "ARID", "DESERT", "NORDIC", "POLAR" };
		for (int i = 0; i < 9; i++) {
			uitext.setString(clmStr[i]);
			uitext.setPosition(32, 16 * i + 8);
			uiElemnts.push_back(new sf::Text(uitext));
		}
		for (int i = 0; i < 9; i++) {
			uitext.setString("0");
			uitext.setPosition(136, 16 * i + 8);
			uiElemnts.push_back(new sf::Text(uitext));
			clmCountPtr[i] = (sf::Text*)uiElemnts[9 + i];
		}
		for (int i = 0; i < 9; i++) {
			tintTile(&uiSprite, CLIMATE(i));
			uiSprite.setPosition(8, 16 * i + 8);
			uiElemnts.push_back(new sf::Sprite(uiSprite));
		}
	}


	gameWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeights), "Game");
	while (run) {
		if (update) {
			WorldMap* wMap = editor.getROworldMap();
			if (wMap->sizeX * wMap->sizeY > 0) {
				for (int i = 0; i < 9; i++) {
					clmCounts[i] = 0;
				}

				if (sprites.size() > wMap->sizeX * wMap->sizeY) {
					sprites.clear();
				}
				sprites.reserve(wMap->sizeX * wMap->sizeY);


				for (int y = 0; y < wMap->sizeY; y++) {
					for (int x = 0; x < wMap->sizeX; x++) {
						CLIMATE tileClimate;
						WORLDOBJECT primSpawn;
						sf::Sprite tileSprite = sf::Sprite(tileTexture[0]);
						tileSprite.setPosition(x * 32, y * 32);
						//tileSprite.setScale(0.5f, 0.5f);
						wMap->regions[x + y * wMap->sizeX].getRegionInfo(&tileClimate, nullptr, nullptr, nullptr, &primSpawn);
						clmCounts[tileClimate]++;
						if (primSpawn) {
							tileSprite.setTexture(tileTexture[1]);
						}

						tintTile(&tileSprite, tileClimate);
						if(x + y * wMap->sizeX >= sprites.size())
							sprites.push_back(tileSprite);
						else
							sprites[x + y * wMap->sizeX] = tileSprite;
					}
					for (int i = 0; i < 9; i++) {
						clmCountPtr[i]->setString(std::to_string(clmCounts[i]));
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
			if (sfevent.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					moveView(-1, 0, 10);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					moveView(0, 1, 10);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					moveView(1, 0, 10);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					moveView(0, -1, 10);

				}
			}
			if (sfevent.type == sf::Event::MouseWheelScrolled) {
				sf::View current = gameWindow->getView();
				current.zoom(1.f + (sfevent.mouseWheelScroll.delta / 100.f));
				gameWindow->setView(current);

			}
		}


		gameWindow->clear();

		if(sprites.size() > 0)
			for (sf::Sprite &sprite : sprites) {
				gameWindow->draw(sprite);
			}
		renderUI();

		gameWindow->display();
	}
	for (sf::Drawable* element : uiElemnts) {
		delete element;
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