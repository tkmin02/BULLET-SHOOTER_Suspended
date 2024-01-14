#pragma once
#include "../../DxLibEngine.h"

class Score;

class ScoreManager {

public:

	static ScoreManager& GetInstance() {

		static ScoreManager instance;
		return instance;
	}

	void InitScoreInstance();

	void AddHitScore(int points);

	void AddComboScore(int points);

	void AddKillBonus(int points);

	void AddSpellCardBonus(int points);

	int GetHitScore() const;

	int GetComboScore() const;

	int GetKillBonus() const;

	int GetSpellCardBonus() const;

	int GetTotalScore() const;

	void RenderTotalScore();

private:

	Shared<Score> hitScore = nullptr;
	Shared<Score> comboScore = nullptr;
	Shared<Score> killBonus = nullptr;
	Shared<Score> spellCardBonus = nullptr;
};