#pragma once
#ifdef DX_GRAPHIC_CONTROL_NOEXCEPT
#define DX_CNOEXCEPT const noexcept
#define DX_NOEXCEPT noexcept
#else
#define DX_CNOEXCEPT const
#define DX_NOEXCEPT
#endif
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
	void Graph(const Coordinate LeftTop, const bool Trans = true) DX_CNOEXCEPT;
	void Graph(const Coordinate LeftTop, const Coordinate RightBottom, const bool Trans = true) DX_CNOEXCEPT;
	Coordinate GetGraphSize() DX_CNOEXCEPT;
};

class GraphicManager {
private:
	std::map<std::string, DxGraphic> GraphicDataBuf;
public:
	GraphicManager() : GraphicDataBuf() {}
	void AddGraphic(const std::string& Key, const std::string& FilePath);
	void Graph(const std::string& Key, const Coordinate LeftTop, const Coordinate RightBottom = { -1, -1 }, const bool Trans = false) DX_CNOEXCEPT;
};
