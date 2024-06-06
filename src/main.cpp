#include "game.h"

int main(int argc, char* argv[]) {
	Game polygame = Game("POLY\0", 640, 480, POLYGINE::WF::TYPICAL);
	polygame.run();
	return 0;
}
