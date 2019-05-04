#pragma once
#include "Number.hpp"
#include "QuizData.hpp"
#include <random>
#include <functional>

class ComputerAnswer {
private:
	std::bernoulli_distribution rand;
	std::reference_wrapper<std::mt19937> RndEng;
	standard::number<unsigned short> Answer(const standard::number<unsigned short>& CorrectAnswer) const {
		static std::uniform_int_distribution<unsigned short> ChooseAnswer(0, 3);
		const standard::number<unsigned short> answer = { ChooseAnswer(this->RndEng), 3, 0 };
		return answer == CorrectAnswer ? this->Answer(CorrectAnswer) : answer;
	}
public:
	ComputerAnswer(const standard::number<float>& CorrectRate, std::mt19937& RandEngine)
		: rand(CorrectRate.Get()), RndEng(RandEngine) {}
	standard::number<unsigned short> Answer(const QuizData& quiz) const {
		return this->rand(this->RndEng.get()) ? quiz.CorrectAnswer : this->Answer(quiz.CorrectAnswer);
	}
};
