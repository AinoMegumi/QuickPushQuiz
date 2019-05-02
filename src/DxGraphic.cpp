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

void DxGraphic::Graph(const Coordinate LeftTop, const bool Trans) DX_CNOEXCEPT {
#ifdef DX_GRAPHIC_CONTROL_NOEXCEPT
	DxLib::DrawGraph(LeftTop.X, LeftTop.Y, this->Handle, Trans ? TRUE : FALSE);
#else
	if (-1 == DxLib::DrawGraph(LeftTop.X, LeftTop.Y, this->Handle, Trans ? TRUE : FALSE)) throw std::runtime_error("Error in DrawGraph function");
#endif
}

void DxGraphic::Graph(const Coordinate LeftTop, const Coordinate RightBottom, const bool Trans) DX_CNOEXCEPT {
#ifdef DX_GRAPHIC_CONTROL_NOEXCEPT
	DxLib::DrawExtendGraph(LeftTop.X, LeftTop.Y, RightBottom.X, RightBottom.Y, this->Handle, Trans ? TRUE : FALSE);
#else
	if (-1 == DxLib::DrawExtendGraph(LeftTop.X, LeftTop.Y, RightBottom.X, RightBottom.Y, this->Handle, Trans ? TRUE : FALSE))
		throw std::runtime_error("Error in DrawExtendGraph function");
#endif
}

Coordinate DxGraphic::GetGraphSize() DX_CNOEXCEPT {
	Coordinate Size{};
	if (-1 == DxLib::GetGraphSize(this->Handle, &Size.X, &Size.Y))
#ifdef DX_GRAPHIC_CONTROL_NOEXCEPT
		return { 0, 0 };
#else
		throw std::runtime_error("Error in GetGraphSize function");
#endif
	return Size;
}

void GraphicManager::AddGraphic(const std::string& Key, const std::string& FilePath) {
	this->GraphicDataBuf.emplace(Key, std::move(DxGraphic(FilePath)));
}

void GraphicManager::Graph(const std::string& Key, const Coordinate LeftTop, const Coordinate RightBottom, const bool Trans) DX_CNOEXCEPT {
	if (RightBottom.X == -1 && RightBottom.Y == -1)	this->GraphicDataBuf.at(Key).Graph(LeftTop, Trans);
	else if (RightBottom.X != -1 && RightBottom.Y != -1) this->GraphicDataBuf.at(Key).Graph(LeftTop, RightBottom, Trans);
	else {
		const Coordinate SizeData = this->GraphicDataBuf.at(Key).GetGraphSize();
		Coordinate GraphRightBottom = RightBottom;
		if (RightBottom.X == -1) GraphRightBottom.X = SizeData.X;
		if (RightBottom.Y == -1) GraphRightBottom.Y = SizeData.Y;
		this->GraphicDataBuf.at(Key).Graph(GraphRightBottom, Trans);
	}
}
