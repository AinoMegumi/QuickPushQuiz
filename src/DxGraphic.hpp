#pragma once
#include "Coordinate.hpp"
#include <string>
#include <map>

class DxGraphic {
private:
	int Handle;
public:
	DxGraphic() = default;
	DxGraphic(const std::string& FilePath);
	~DxGraphic() noexcept;
	DxGraphic(const DxGraphic&) = delete;
	DxGraphic(DxGraphic&& d) noexcept;
	DxGraphic& operator = (const DxGraphic&) = delete;
	DxGraphic& operator = (DxGraphic&& d) noexcept;
	void Graph(const Coordinate::Absolute LeftTop, const bool Trans = true) const noexcept;
	void Graph(const Coordinate::Absolute LeftTop, const Coordinate::Absolute RightBottom, const bool Trans = true) const noexcept;
	Coordinate::Absolute GetGraphSize() const noexcept;
};

class GraphicManager {
private:
	std::map<std::string, DxGraphic> GraphicDataBuf;
public:
	GraphicManager() : GraphicDataBuf() {}
	void AddGraphic(const std::string& Key, const std::string& FilePath);
	void Graph(const std::string& Key, const Coordinate::Absolute LeftTop, const Coordinate::Absolute RightBottom = { -1, -1 }, const bool Trans = false) const noexcept;
};
