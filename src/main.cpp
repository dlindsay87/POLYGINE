#include "game.h"
#include "flecs.h"

void printHelp()
{
	std::cout << "Usage: ./polygine [options]\n";
	std::cout << "	Options:\n";
	std::cout << "    -sd, --shaderDev  : Use imGUI to tweak shaders\n";
	std::cout << "    -h, --help        : Display this help message.\n";
}

int main(int argc, char **argv)
{
	bool shaderDev = false;
	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (strcmp("--help", arg) == 0 || strcmp("-h", arg) == 0) {
			printHelp();
			return 0;
		}
		if (strcmp("--shadeDev", arg) == 0 || strcmp("-sd", arg) == 0)
			shaderDev = true;
	}

	GAME::Game game(shaderDev);
	game.run();
	return 0;
}
