#pragma once
#include "Core.hpp"

// 絶対座標系
struct Coordinate {
	Coordinate() = default;
	constexpr Coordinate(const int X, const int Y) : x(X), y(Y) {}	
	int x;
	int y;
};

// 相対座標系
struct Position {
	Position() = default;
	constexpr Position(const float X, const float Y) : x(X), y(Y) {}
	Coordinate ToCoordinate() const;
	Position operator << (const Coordinate& c);
	float x, y;
};

void operator << (Coordinate &c, const Position p) {
	c = { static_cast<int>(static_cast<float>(Core::DisplayWidth) * p.x + 0.5), static_cast<int>(static_cast<float>(Core::DisplayHeight) * p.y + 0.5) };
}

void operator << (Position &p, const Coordinate & c) {
	p = { static_cast<float>(c.x) / static_cast<float>(Core::DisplayWidth), static_cast<float>(c.y) / static_cast<float>(Core::DisplayHeight) };
}
