#pragma once

class BulletHell;

// 特定の弾幕パターンを生成

class BulletHellFactory
{
public:

	BulletHellFactory();

	void InitBulletHellInfo();

	std::list<Shared<EnemyBullet>> CreateBulletHell(const BulletHell::TYPE type);

	Shared<EnemyBullet> ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map,int id);

	Shared<EnemyBullet> GetBulletHellsBullet(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

private:

	//// <summary>
	//  ※ (パチュリー専用)
	// 円形連続発射と、ランダムにゆっくり落ちてくる弾を組み合わせた弾幕
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_SilentSerena();

	//// <summary>
	//  ※ (チルノ専用)
	// 1.全方向ばら撒きショットをうつ
	// 2.フリーズ、弾を止めて白くする
	// 3.自機依存された８方向ショットを連続でうつ
	// 4.止めていた弾を全方向で動かし始める
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_PerfectFreeze();

	//// <summary>
	//　※ (諏訪子専用)
	//　1.上に向かって8way弾を撃つ
	//　2.徐々に下向きに加速していく
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();

private:

	Shared<CsvLoader> _csvLoader = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};

	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;
};