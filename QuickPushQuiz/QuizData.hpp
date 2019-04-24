#pragma once
#include "Number.hpp"
#include <string>
#include <vector>
#include <array>

struct QuizData {
public:
	QuizData() = default;
	QuizData(const std::string& FilePath);
	static std::vector<QuizData> LoadQuizData(const std::string& QuizRootDir);
	std::string Question;
	std::array<std::string, 4> AnswerGroup;
	standard::number<unsigned short> CorrectAnswer;
};
