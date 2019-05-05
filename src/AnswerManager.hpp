#pragma once
class AnswerManager {
private:
	bool PlayerAnswered;
	bool EnemyAnswered;
public:
	AnswerManager() : PlayerAnswered(false), EnemyAnswered(false) {}
	void Reset() {
		this->PlayerAnswered = false;
		this->EnemyAnswered = false;
	}
	void SetPlayerAnswered() { this->PlayerAnswered = true; }
	void SetEnemyAnswered() { this->EnemyAnswered = true; }
	bool loop() const noexcept { return !this->PlayerAnswered || !this->EnemyAnswered; }
};
