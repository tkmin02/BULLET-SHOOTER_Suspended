#pragma once

class BulletHell;
class EnemyManager;

// 特定の弾幕パターンを生成

class BulletHellFactory
{
public:

	BulletHellFactory(){}

	explicit BulletHellFactory(const Shared<EnemyManager>& enemyManager);

	void InitBulletHellInfo();

	std::list<Shared<EnemyBullet>> CreateBulletHell(const BulletHell::TYPE type);

	Shared<EnemyBullet> ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

	Shared<EnemyBullet> GetBulletHellsBullet(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

private:

	//// <summary>
    //  ※ (パチュリー専用)
    // 1.ボスの周囲に4つの巨大な弾を生成
	// 2.その弾から直線に光線を放つ
	// 3.光線を放ちながら左回転
	// 4.ボスの周囲に新たな4つの巨大な弾を生成
	// 5.同じように弾から直線に光線を放ち、今度は右回転
	// 6.左回転をしている弾と光線を消去
	// 7.右回転をしている弾と光線を消去
	// 8.四方八方に４連続で弾を発射
	// 9.左回転、右回転の技に合わせ、四方八方に４連続で弾を発射
    //// </summary>
    std::list<Shared<EnemyBullet>> CreateBulletHell_Normal_Patchouli();


	//// <summary>
	//  ※ (パチュリー専用)
	// 円形連続発射と、ランダムにゆっくり近づいてくる弾を組み合わせた弾幕
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_SilentSerena_Patchouli();


	//// <summary>
    //  ※ (パチュリー専用)
    // 円状に8way弾が展開され、途中でそれぞれが8way弾に増える。
    //// </summary>
    std::list<Shared<EnemyBullet>> CreateBulletHell_MetalFatigue_Patchouli();

	//// <summary>
	/// ※　CreateBulletHell_MetalFatigue_Patchouli関数で使用する弾幕生成ロジックの関数化
	/// </summary>
	/// <param name="split_one_into_eight_WAVE1"></param>
	/// <param name="split_one_into_eight_bullet"></param>
	//// <param name="enemyBullet"></param>
	void InitSplitOneIntoEightBullet(int split_one_into_eight_WAVE1, Shared<EnemyBullet>& split_one_into_eight_bullet, std::list<Shared<EnemyBullet>>& enemyBullet, const std::string& wave);



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

	Shared<BulletHell> _bulletHell = nullptr;

	Shared<EnemyManager> _enemyManager = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};

	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;


};