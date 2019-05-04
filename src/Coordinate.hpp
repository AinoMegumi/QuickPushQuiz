#pragma once
struct Position;

// 絶対座標系
struct Coordinate {
	Coordinate() = default;
	constexpr Coordinate(const int X, const int Y) : x(X), y(Y) {}
	Position ToPosition() const;
	Coordinate operator << (const Position& p);
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
