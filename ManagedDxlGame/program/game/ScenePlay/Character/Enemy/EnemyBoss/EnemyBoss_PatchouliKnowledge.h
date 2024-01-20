#pragma once
#include "../EnemyBase.h"

class BulletHell;

class EnemyBoss_PatchouliKnowledge : public EnemyBase
{
public:

	EnemyBoss_PatchouliKnowledge() {}
	EnemyBoss_PatchouliKnowledge(Shared<EnemyBoss_PatchouliKnowledge> boss) {}
	EnemyBoss_PatchouliKnowledge(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);


	void SetMeshInfo() override;

	void AttackPlayer(const float& delta_time) override;

	void InitBulletHellInstance() override;

	void DoRoutineMoves(float delta_time) override;

	void UpdateBulletHell(const float delta_time);

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;


private:

	Shared<BulletHell> _bulletHell = nullptr;

private:

	static std::list<Shared<EnemyBullet>> _bullet_patchouli;


	int _MAX_HP;
};
