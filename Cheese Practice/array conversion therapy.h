#pragma once
#include <string>
#include <array>
#include <iostream>
#include "real pieces.h"

std::string movelistToString(std::array<std::array<int, 2>, 2> move, Piece * piece);

std::string gridToNotate(std::array<int, 2> location);