#pragma once
#include "../DxLibEngine.h"

class Player;
class EnemyBoss_PatchouliKnowledge;
class BulletHell;


struct EnemyZakoInfo
{
	int _id{};
	int _scale{};
	int _stageID{};

	int _hp{};
	int _maxBulletSpawnCount{};
	int _maxTotalEnemySpawnCount{};	// ゲーム全体で存在できる実体の最大数

	float _charaMoveSpeed{};
	std::string _name{};
};

struct EnemyBossInfo
{
	int _id{};
	int _stageID{};
	int _scale{};
	int _hp{};
	int _maxBulletSpawnCount{};
	float _charaMoveSpeed{};
	std::string _name{};
};

struct BulletHellType_Info
{
	int _id{};
	int _maxBulletSpawnCount{};
	float _bulletSpawnRate{};
	std::string _typeName{};
};


class CsvLoader
{
public:

	CsvLoader() {}
	CsvLoader(const std::string difficulty) : _SELECTED_DIFFICULTY(difficulty) {}
	CsvLoader(int value) {}


	std::unordered_map<int, EnemyZakoInfo> LoadEnemyZakoInfos(const std::string enemy_csv);
	std::unordered_map<int, EnemyBossInfo> LoadEnemyBossInfos(const std::string enemy_csv);
	std::unordered_map<int, BulletHellType_Info> LoadBulletHellTypeInfos(const std::string enemy_csv);

private:

	const std::string _SELECTED_DIFFICULTY;
};
