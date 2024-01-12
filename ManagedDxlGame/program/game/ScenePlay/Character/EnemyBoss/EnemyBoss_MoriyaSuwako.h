#pragma once
#include "../Enemy/EnemyBase.h"

class BulletHell;

class EnemyBoss_MoriyaSuwako : public EnemyBase
{
public:

	EnemyBoss_MoriyaSuwako() {}
	EnemyBoss_MoriyaSuwako(Shared<EnemyBoss_MoriyaSuwako> boss) {}
	EnemyBoss_MoriyaSuwako(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);


	void SetMeshInfo() override;

	void AttackPlayer(float delta_time) override;

	//bool ShowHpGage_EnemyZako() override;

	void LookAtPlayer(const float delta_time) override;

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;


public:

	Shared<BulletHell> _bulletHell = nullptr;

private:

	int _MAX_HP;
};

