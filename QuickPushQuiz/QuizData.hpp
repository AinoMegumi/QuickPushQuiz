#pragma once
#include "Number.hpp"
#include <string>
#include <vector>
#include <array>

class QuizData {
public:
	QuizData() = default;
private:
	QuizData(const std::string& FilePath);
public:
	static std::vector<QuizData> LoadQuizData(const std::string& QuizRootDir);
	std::string Question;
	std::array<std::string, 4> AnswerGroup;
	standard::number<unsigned short> CorrectAnswer;
};
