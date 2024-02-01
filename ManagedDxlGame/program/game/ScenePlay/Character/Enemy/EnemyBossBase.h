#pragma once
#include "EnemyBase.h"

class Player;
class BulletHell;
class EnemyBullet;
class CsvLoader;
struct EnemyBossInfo;

class EnemyBossBase : public EnemyBase
{
public:

	EnemyBossBase(){}

	EnemyBossBase(const EnemyBossInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	virtual void InitBulletHellInstance() {}

	void DecreaseBossHP(int damage);

protected:

	virtual bool ShowHpGage_EnemyBoss();

	virtual void RenderBossRemainLife();

	virtual void RenderBossSpellCardName() {}

	void ActKeepDistanceToPlayer(const float& delta_time);

	void RenderBossName();

public:

	static std::deque<int> _bossHp;

protected:

	std::list<Shared<EnemyBossBase>> _enemyBoss_list_ref;

private:

	std::stack<std::deque<int>> _remaining_life_indicator;
};