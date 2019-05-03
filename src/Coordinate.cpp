#include "Coordinate.hpp"
#include "Core.hpp"

Coordinate Coordinate::operator<<(const Position& p) {
	return { static_cast<int>(Core::DisplayWidth * p.x + 0.5), static_cast<int>(Core::DisplayHeight * p.y + 0.5) };
}

Position Position::operator<<(const Coordinate& c) {
	return { static_cast<float>(c.x) / Core::DisplayWidth, static_cast<float>(c.y) / Core::DisplayHeight };
}
