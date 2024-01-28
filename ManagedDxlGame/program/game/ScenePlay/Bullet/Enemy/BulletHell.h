#pragma once
#include "EnemyBullet.h"

class BulletHellFactory;
class ScenePlay;


struct SpawnedBossBulletInfo {
	tnl::Vector3 originPos;
	tnl::Vector3 moveDirection;
};


// �e�̐����A�e���̃p�^�[���A�e�̍X�V�ƍ폜�Ȃǂ��s�� (EnemyBoss����)
// �{�X�͒ʏ�U���A�X�y���J�[�h1�A�X�y���J�[�h2�̌v�R��ނ̒e�������

class BulletHell : public EnemyBullet
{
public:

	enum class TYPE {

		None,
		Normal_Patchouli,
		SilentSerena_Patchouli,
		MetalFatigue_Patchouli,
		Perfect_Freeze,
		KeroChan_StandsFirm_AgainstTheStorm,
	};

public:

	BulletHell() {}
	BulletHell(const Shared<dxe::Mesh>& bossMesh);

	void RemoveBullet(Shared<EnemyBullet> bullet);
	void Clear();

	// 1�X�e�[�W�{�X�i�p�`�����[�j-------------------------------
	void ShotBulletHell_Normal_Patchouli(const float& delta_time);
	void ShotBulletHell_SilentSerena_Patchouli(const float& delta_time);
	void ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time);
	// -------------------------------------------------------------

	// 2�X�e�[�W�{�X�i
	void ShotBulletHell_PerfectFreeze(const float& delta_time);
	// 3�X�e�[�W�{�X
	void ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time);

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