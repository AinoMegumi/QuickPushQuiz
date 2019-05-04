#include "DxGraphic.hpp"
#include "DxLib.h"
#include <fstream>

static inline int DxLoadGraph(const std::string& FilePath) {
	if (std::ifstream ifs(FilePath); !ifs.good()) throw std::runtime_error(FilePath + " : File is not found");
	if (const int GHandle = DxLib::LoadGraph(FilePath.c_str()); GHandle == -1) throw std::runtime_error(FilePath + " : Error in LoadGraph function.");
	else return GHandle;
}

DxGraphic::DxGraphic(const std::string& FilePath) 
	: Handle(DxLoadGraph(FilePath)) {}

DxGraphic::~DxGraphic() noexcept { DxLib::DeleteGraph(this->Handle); }

DxGraphic::DxGraphic(DxGraphic&& d) noexcept : Handle(std::move(d.Handle)) { d.Handle = -1; }

DxGraphic& DxGraphic::operator = (DxGraphic&& d) noexcept {
	this->Handle = std::move(d.Handle);
	d.Handle = -1;
	return *this;
}

void DxGraphic::Graph(const Coordinate LeftTop, const bool Trans) const noexcept {
	DxLib::DrawGraph(LeftTop.x, LeftTop.y, this->Handle, Trans ? TRUE : FALSE);
}

void DxGraphic::Graph(const Coordinate LeftTop, const Coordinate RightBottom, const bool Trans) const noexcept {
	DxLib::DrawExtendGraph(LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y, this->Handle, Trans ? TRUE : FALSE);
}

Coordinate DxGraphic::GetGraphSize() const noexcept {
	Coordinate Size{};
	return -1 == DxLib::GetGraphSize(this->Handle, &Size.x, &Size.y) ? Coordinate(0, 0) : Size;
}

void GraphicManager::AddGraphic(const std::string& Key, const std::string& FilePath) {
	this->GraphicDataBuf.emplace(Key, DxGraphic(FilePath));
}

void GraphicManager::Graph(const std::string& Key, const Coordinate LeftTop, const Coordinate RightBottom, const bool Trans) const noexcept {
	if (RightBottom.x == -1 && RightBottom.y == -1)	this->GraphicDataBuf.at(Key).Graph(LeftTop, Trans);
	else if (RightBottom.x != -1 && RightBottom.y != -1) this->GraphicDataBuf.at(Key).Graph(LeftTop, RightBottom, Trans);
	else {
		const Coordinate SizeData = this->GraphicDataBuf.at(Key).GetGraphSize();
		Coordinate GraphRightBottom = RightBottom;
		if (RightBottom.x == -1) GraphRightBottom.x = SizeData.x;
		if (RightBottom.y == -1) GraphRightBottom.y = SizeData.y;
		this->GraphicDataBuf.at(Key).Graph(GraphRightBottom, Trans);
	}
}
