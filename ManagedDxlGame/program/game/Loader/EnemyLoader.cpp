#include "EnemyLoader.h"
#include "../ScenePlay/Character/Player/Player.h"



std::unordered_map<int, EnemyZakoInfo> EnemyLoader::LoadEnemyZakoInfos(const std::string enemy_csv) {

	std::unordered_map<int, EnemyZakoInfo> infos;

	auto csv = tnl::LoadCsv(enemy_csv);

	for (int i = 1; i < csv.size(); i++) {

		EnemyZakoInfo data;

		data._id = csv[i][0].getInt();
		data._scale = csv[i][1].getInt();
		data._name = csv[i][2].getString();

		if (_SELECTED_DIFFICULTY == "Easy") {
			data._hp = csv[i][3].getInt();
			data._maxBulletSpawnCount = csv[i][7].getInt();
			data._maxTotalEnemySpawnCount = csv[i][11].getInt();
			data._charaMoveSpeed = csv[i][15].getFloat();
		}
		else if (_SELECTED_DIFFICULTY == "Normal") {
			data._hp = csv[i][4].getInt();
			data._maxBulletSpawnCount = csv[i][8].getInt();
			data._maxTotalEnemySpawnCount = csv[i][12].getInt();
			data._charaMoveSpeed = csv[i][16].getFloat();

		}
		else if (_SELECTED_DIFFICULTY == "Hard") {
			data._hp = csv[i][5].getInt();
			data._maxBulletSpawnCount = csv[i][9].getInt();
			data._maxTotalEnemySpawnCount = csv[i][13].getInt();
			data._charaMoveSpeed = csv[i][17].getFloat();

		}
		else if (_SELECTED_DIFFICULTY == "Lunatic") {
			data._hp = csv[i][6].getInt();
			data._maxBulletSpawnCount = csv[i][10].getInt();
			data._maxTotalEnemySpawnCount = csv[i][14].getInt();
			data._charaMoveSpeed = csv[i][18].getFloat();

		}


		infos[data._id] = data;
	}

	return infos;
}



std::unordered_map<int, EnemyBossInfo> EnemyLoader::LoadEnemyBossInfos(const std::string enemy_csv) {

	std::unordered_map<int, EnemyBossInfo> infos;

	auto csv = tnl::LoadCsv(enemy_csv);

	for (int i = 1; i < csv.size(); i++) {

		EnemyBossInfo data;

		data._id = csv[i][0].getInt();
		data._scale = csv[i][1].getInt();
		data._name = csv[i][2].getString();


		if (_SELECTED_DIFFICULTY == "Easy") {
			data._hp = csv[i][3].getInt();
			data._maxBulletSpawnCount = csv[i][7].getInt();
			data._charaMoveSpeed = csv[i][11].getFloat();
		}
		else if (_SELECTED_DIFFICULTY == "Normal") {
			data._hp = csv[i][4].getInt();
			data._maxBulletSpawnCount = csv[i][8].getInt();
			data._charaMoveSpeed = csv[i][12].getFloat();
		}
		else if (_SELECTED_DIFFICULTY == "Hard") {
			data._hp = csv[i][5].getInt();
			data._maxBulletSpawnCount = csv[i][9].getInt();
			data._charaMoveSpeed = csv[i][13].getFloat();
		}
		else if (_SELECTED_DIFFICULTY == "Lunatic") {
			data._hp = csv[i][6].getInt();
			data._maxBulletSpawnCount = csv[i][10].getInt();
			data._charaMoveSpeed = csv[i][14].getFloat();
		}


		infos[data._id] = data;
	}

	return infos;
}