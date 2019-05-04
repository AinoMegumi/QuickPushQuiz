#include "Coordinate.hpp"
#include "Core.hpp"

Coordinate Coordinate::operator<<(const Position& p) {
	return { static_cast<int>(static_cast<float>(Core::DisplayWidth) * p.x + 0.5), static_cast<int>(static_cast<float>(Core::DisplayHeight) * p.y + 0.5) };
}

Position Position::operator<<(const Coordinate& c) {
	return { static_cast<float>(c.x) / static_cast<float>(Core::DisplayWidth), static_cast<float>(c.y) / static_cast<float>(Core::DisplayHeight) };
}

Position Coordinate::ToPosition() const {
	return { static_cast<float>(this->x) / static_cast<float>(Core::DisplayWidth), static_cast<float>(this->y) / static_cast<float>(Core::DisplayHeight) };
}

Coordinate Position::ToCoordinate() const {
	return { static_cast<int>(static_cast<float>(Core::DisplayWidth) * this->x + 0.5), static_cast<int>(static_cast<float>(Core::DisplayHeight) * this->y + 0.5) };
}
