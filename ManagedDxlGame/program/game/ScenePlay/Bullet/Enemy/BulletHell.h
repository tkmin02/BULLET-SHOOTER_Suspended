#pragma once
#include "EnemyBullet.h"

class BulletHellFactory;
class ScenePlay;

struct SpawnedBossBulletInfo {
	tnl::Vector3 originPos;
	tnl::Vector3 moveDirection;
};



// 弾の生成、弾幕のパターン、弾の更新と削除などを行う (EnemyBoss限定)
// ボスは通常攻撃、スペルカード1、スペルカード2の計３種類の弾幕を放つ

class BulletHell : public EnemyBullet
{
public:

	enum class TYPE {

		None,
		// パチュリー
		Normal_Patchouli,
		MetalFatigue_Patchouli,
		SilentSerena_Patchouli,
		// チルノ
		Normal_Cirno,
		IcicleFall_Cirno,
		Perfect_Freeze_Cirno,
		// 諏訪子
		KeroChan_StandsFirm_AgainstTheStorm_Suwako,
	};

public:

	BulletHell() {}
	BulletHell(const Shared<dxe::Mesh>& bossMesh);

	// ステージ1ボス（パチュリー）-------------------------------------
	void ShotBulletHell_Normal_Patchouli(const float& delta_time);
	void ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time);
	void ShotBulletHell_SilentSerena_Patchouli(const float& delta_time);
	// ステージ2ボス（チルノ）---------------------------------------------
	void ShotBulletHell_Normal_Cirno(const float& delta_time);
	void ShotBulletHell_IcicleFall_Cirno(const float& delta_time);
	void ShotBulletHell_PerfectFreeze_Cirno(const float& delta_time);
	// ステージ3ボス（諏訪子）---------------------------------------------
	void ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time);


	// ---------------------------------------------

	void CheckLifeTimeDistance(Shared<EnemyBullet>& it_bltHell);

	tnl::Vector3& GetCurrentBossPosition() { return _bossMesh_ref->pos_; }


private:

	const Shared<dxe::Mesh> _bossMesh_ref = nullptr;
	std::map<int, Shared<EnemyBullet>> _bltHellsBlt_map;

public:

	static int currentBulletNum;

	int bullet_count{};
	int bullet_speed{};
};