#pragma once
#include "Core.hpp"

namespace Coordinate {
	// 絶対座標系
	struct Absolute {
		Absolute() = default;
		constexpr Absolute(const int X, const int Y) : x(X), y(Y) {}
		int x;
		int y;
	};

	// 相対座標系
	struct Relative {
		Relative() = default;
		constexpr Relative(const float X, const float Y) : x(X), y(Y) {}
		float x, y;
	};

	inline Absolute to(const Relative& r) { 
		return Absolute(
			static_cast<int>(static_cast<float>(Core::DisplayWidth) * r.x + 0.5),
			static_cast<int>(static_cast<float>(Core::DisplayHeight) * r.y + 0.5)
		);
	}
	inline Relative to(const Absolute& a) {
		return Relative(
			static_cast<float>(a.x) / static_cast<float>(Core::DisplayWidth),
			static_cast<float>(a.y) / static_cast<float>(Core::DisplayHeight)
		);
	}
}
