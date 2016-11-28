#pragma once
#include <string>
#include <array>
#include <iostream>
#include "real pieces.h"

//special moves -> 0 for not special; 1 for castle; 2 for promotion; 3 for en passant
std::string movelistToString(std::array<std::array<int, 2>, 2> move, Piece * piece, int specialMove);

std::string gridToNotate(std::array<int, 2> location, int specialMove);