#pragma once
struct Coordinate {
	int x;
	int y;
};

// 相対座標系
struct Position {
	Position() = default;
	constexpr Position(const float X, const float Y) : x(X), y(Y) {}
	Position operator << (const Coordinate& c);
	float x, y;
};
