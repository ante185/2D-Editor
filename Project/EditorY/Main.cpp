#include "editor.h"

//const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
//const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
//const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
//const	char*	largeWorld	=	"../../worldmap/large_world.ybin";






int main() {
	std::string welcome = "Welcome to the editor, type \"help\" for commands";

	std::cout << welcome << std::endl;

	Editor editor;
	std::cout << std::endl << '>';
	while(editor.update());


	return 0;
}