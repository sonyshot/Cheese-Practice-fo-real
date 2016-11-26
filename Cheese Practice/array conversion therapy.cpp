#include "array conversion therapy.h"

std::string movelistToString(std::array<std::array<int, 2>, 2> move) {
	std::string output;
	output.append("(" + std::to_string(move[0][0]) + ", " + std::to_string(move[0][1]) + ")->( " + std::to_string(move[1][0]) + ", " + std::to_string(move[1][1]) + ")\n");
	return output;
};