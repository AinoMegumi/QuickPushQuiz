#pragma once
#include "GameController.hpp"
#include <functional>

class QuizScreenController {
private:
	std::reference_wrapper<GameController> Controller;
public:
	QuizScreenController(GameController& controller) : Controller(controller) {}
};
