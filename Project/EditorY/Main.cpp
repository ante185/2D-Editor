#include "editor.h"

const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
const	char*	largeWorld	=	"../../worldmap/large_world.ybin";






int main() {
	
	Editor editor;
	while(editor.update());


	return 0;
}