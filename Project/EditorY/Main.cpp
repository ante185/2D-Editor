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
static sf::Texture noneTexture;

class drawableRegion : public sf::Drawable {
public:
	sf::Sprite relief;
	sf::Sprite vegetation;
	sf::Sprite waterFeature;
	sf::Sprite primSpawn;

	drawableRegion() {
		relief.setTexture(noneTexture);
		vegetation.setTexture(noneTexture);
		waterFeature.setTexture(noneTexture);
		primSpawn.setTexture(noneTexture);
	}
	void setPosition(float x, float y){
		relief.setPosition(x, y);
		vegetation.setPosition(x, y);
		waterFeature.setPosition(x, y);
		primSpawn.setPosition(x, y);
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override
	{
		target.draw(relief);
		target.draw(vegetation);
		target.draw(waterFeature);
		target.draw(primSpawn);
	}

};
Editor editor;
std::vector<drawableRegion> sprites;
std::vector<sf::Drawable*> uiElemnts;
sf::RenderWindow* gameWindow = nullptr;
bool run = true;
bool update = false;



void tintTile(sf::Sprite *tile, CLIMATE clm) {
	tile->setColor(tileTints[(int)clm]);
}
void tintTile(drawableRegion *tile, CLIMATE clm) {
	tile->relief.setColor(tileTints[(int)clm]);
	tile->vegetation.setColor(tileTints[(int)clm]);
	tile->waterFeature.setColor(tileTints[(int)clm]);
	tile->primSpawn.setColor(tileTints[(int)clm]);
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
	sf::Texture tileTexture[7];
	noneTexture.loadFromFile("../../images/none.png");
	{
		sf::String texturePath[]{ "../../images/default.png", "../../images/plains.png", "../../images/rocky.png", "../../images/hills.png", "../../images/mountains.png", "../../images/forest.png", "../../images/spawn.png" };
		for (int i = 0; i < 7; i++) {
			tileTexture[i].loadFromFile(texturePath[i]);
		}
	}
	
	
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
						RELIEF relief;
						VEGETATION vegetation;
						WATER waterFeature;
						WORLDOBJECT primSpawn;
						drawableRegion tileSprite;
						tileSprite.setPosition(x * 32, y * 32);
						wMap->regions[x + y * wMap->sizeX].getRegionInfo(&tileClimate, &relief, &vegetation, &waterFeature, &primSpawn);
						clmCounts[tileClimate]++;
						switch (relief)
						{
						case RELIEF_NONE:
							tileSprite.relief.setTexture(tileTexture[0]);
							break;
						case PLAIN:
							tileSprite.relief.setTexture(tileTexture[1]);
							break;
						case ROCKY:
							tileSprite.relief.setTexture(tileTexture[2]);
							break;
						case HILLS:
							tileSprite.relief.setTexture(tileTexture[3]);
							break;
						case MOUNTAINS:
							tileSprite.relief.setTexture(tileTexture[4]);
							break;
						default:
							break;
						}
						if (vegetation) {
							tileSprite.vegetation.setTexture(tileTexture[5]);
						}
						if (primSpawn) {
							tileSprite.primSpawn.setTexture(tileTexture[6]);
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
			for (drawableRegion &tile : sprites) {
				gameWindow->draw(tile);
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