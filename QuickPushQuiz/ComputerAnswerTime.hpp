#pragma once
#include <functional>
#include <random>

class ComputerAnswerTime {
private:
	std::uniform_int_distribution<unsigned long long> rand;
	std::reference_wrapper<std::mt19937> RndEng;
public:
	ComputerAnswerTime(const unsigned long long MaxWaitTime, const unsigned long long MinWaitTime, std::mt19937& RandEngine)
		: rand(MinWaitTime, MaxWaitTime), RndEng(RandEngine) {}
	unsigned long long ComputerAnswerTime::Generate() const { return this->rand(this->RndEng.get()); }
};
