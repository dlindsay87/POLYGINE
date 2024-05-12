#include "game.h"

int main() {
	Game polygame = Game(60.0, "POLY\0", 640, 480, POLYGINE::WF::TYPICAL);
	polygame.run();
	return 0;
}
