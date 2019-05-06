#include "MouseController.hpp"
#include "DxLib.h"

void MouseController::UpdateCurrentPos() {
	GetMousePoint(&this->Current.x, &this->Current.y);
}

bool MouseController::Clicked() {
	return Core::LeftHandMouse
		? GetMouseInput() & MOUSE_INPUT_RIGHT
		: GetMouseInput() & MOUSE_INPUT_LEFT;
}
