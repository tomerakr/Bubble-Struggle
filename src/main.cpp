#include "Controller.h"
#include "SFML/Network.hpp"
#include <iostream>

int main() try {

	Controller gameController;
	gameController.play();

	return 0;
}

catch (...) {
	std::cerr << "Exception\n";
	return EXIT_FAILURE;
}
