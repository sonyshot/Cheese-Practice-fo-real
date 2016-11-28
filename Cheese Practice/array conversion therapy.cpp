#include "array conversion therapy.h"

std::string movelistToString(std::array<std::array<int, 2>, 2> move, Piece * piece, int specialMove) {
	if (piece->getColor() == 1) {
		std::string output = "\n" + piece->getName();
		output.append(gridToNotate(move[1], specialMove));
		return output;
	}
	else {
		std::string output = " - " + piece->getName();
		output.append(gridToNotate(move[1], specialMove));
		return output;
	}
};

std::string gridToNotate(std::array<int, 2> grid, int specialMove) {
	std::string output;
	if (!specialMove) {
		switch (grid[0]) {
		case 0:
			output.append("a");
			break;
		case 1:
			output.append("b");
			break;
		case 2:
			output.append("c");
			break;
		case 3:
			output.append("d");
			break;
		case 4:
			output.append("e");
			break;
		case 5:
			output.append("f");
			break;
		case 6:
			output.append("g");
			break;
		case 7:
			output.append("h");
			break;
		};
		output.append(std::to_string(grid[1] + 1));
		return output;
	}
	else if (specialMove == 1) {
		if (grid[0] == 6) {
			output.append("O-O");
			return output;
		}
		else {
			output.append("O-O-O");
			return output;
		}
	}
	else if (specialMove == 2) {
		output.append("||");
		return output;
	}
	else {
		output.append("ep");
		return output;
	}
};