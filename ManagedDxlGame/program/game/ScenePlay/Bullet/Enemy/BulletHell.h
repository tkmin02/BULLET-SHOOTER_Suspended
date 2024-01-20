#pragma once
#include "EnemyBullet.h"

class BulletHellFactory;
//class CsvLoader;

// 弾の生成、弾幕のパターン、弾の更新と削除などを行う (EnemyBoss限定)
class BulletHell : public EnemyBullet
{
public:

	enum class TYPE {

		None,
		Silent_Serena,
		Perfect_Freeze,
		KeroChan_StandsFirm_AgainstTheStorm,
	};

public:

	BulletHell(){}
	BulletHell(const Shared<dxe::Mesh>& bossMesh, std::list<Shared<EnemyBullet>> bossBullet);

	void AddBullet(const Shared<EnemyBullet>& bullet);
	void RemoveBullet(Shared<EnemyBullet> bullet);
	void Clear();


	void ShotBulletHell_SilentSerena(const float& delta_time);
	void CheckLifeTimeDistance(Shared<EnemyBullet>& it_bltHell);
	void ShotBulletHell_PerfectFreeze(const float& delta_time);
	void ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time);


	void Render(Shared<dxe::Camera> _mainCamera) override;
	void Update(float deltaTime) override;


public:

	Shared<BulletHellFactory> _bltHellFactory = nullptr;
	std::list<Shared<EnemyBullet>> _bulletHell_bullets;

private:

	const Shared<dxe::Mesh> _bossMesh_ref = nullptr;
	std::map<int, Shared<EnemyBullet>> _bltHellsBlt_map;

public:


	int bullet_count{};
	int bullet_speed{};
};