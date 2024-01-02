#pragma once
#include "../DxLibEngine.h"

class Player;

struct EnemyInfo
{
	int _id{};
	int _hp{};
	int _scale{};
	int _maxSpawnCount{};
	float _speed{};
	std::string _name{};
};


class EnemyLoader
{
public:

	EnemyLoader() {}
	EnemyLoader(int value) {}


	std::unordered_map<int, EnemyInfo> LoadEnemyInfos(const std::string enemy_csv);
};

