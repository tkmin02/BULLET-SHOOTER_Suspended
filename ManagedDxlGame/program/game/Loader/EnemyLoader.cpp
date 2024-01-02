#include "EnemyLoader.h"
#include "../ScenePlay/Character/Player/Player.h"



std::unordered_map<int, EnemyInfo> EnemyLoader::LoadEnemyInfos(const std::string enemy_csv) {

	std::unordered_map<int, EnemyInfo> infos;

	auto csv = tnl::LoadCsv(enemy_csv);

	for (int i = 1; i < csv.size(); i++) {

		EnemyInfo data;

		data._id = csv[i][0].getInt();
		data._hp = csv[i][1].getInt();
		data._scale = csv[i][2].getInt();
		data._maxSpawnCount = csv[i][3].getInt();
		data._speed = csv[i][4].getFloat();
		data._name = csv[i][5].getString();

		infos[data._id] = data;
	}

	return infos;
}
