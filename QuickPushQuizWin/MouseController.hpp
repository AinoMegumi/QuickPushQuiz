#pragma once
#include "GameController.hpp"

class MouseController : public GameController {
public:
	MouseController() : GameController() {}
	void UpdateCurrentPos() override;
	bool Clicked() override;
};
