#pragma once
#include "EnemyBullet.h"

class BulletHellFactory;
class ScenePlay;
class Player;

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
		// �p�`�����[
		Normal_Patchouli,
		MetalFatigue_Patchouli,
		SilentSerena_Patchouli,
		// �`���m
		Normal_Cirno,
		IcicleFall_Cirno,
		Perfect_Freeze_Cirno,
		// �z�K�q
		Normal_Suwako,
		IronRingOfMoriya_Suwako,
		KeroChan_StandsFirm_AgainstTheStorm_Suwako,
	};

public:

	BulletHell() {}
	BulletHell(const Shared<dxe::Mesh>& bossMesh, const Shared<Player>& player);

	// �X�e�[�W1�{�X�i�p�`�����[�j-------------------------------------
	void ShotBulletHell_Normal_Patchouli(const float& delta_time);
	void ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time);
	void ShotBulletHell_SilentSerena_Patchouli(const float& delta_time);
	// �X�e�[�W2�{�X�i�`���m�j---------------------------------------------
	void ShotBulletHell_Normal_Cirno(const float& delta_time);
	void ShotBulletHell_IcicleFall_Cirno(const float& delta_time);
	void ShotBulletHell_PerfectFreeze_Cirno(const float& delta_time);
	// �X�e�[�W3�{�X�i�z�K�q�j---------------------------------------------
	void ShotBulletHell_Normal_Suwako(const float& delta_time);
	void ShotBulletHell_IronRingOfMoriya_Suwako(const float& delta_time);
	void ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm_Suwako(const float& delta_time);


	// ---------------------------------------------

	void CheckLifeTimeDistance(Shared<EnemyBullet>& bullet, const tnl::Vector3& pos, const float limit_distance);

	const float& GetCurrentBulletMovedDistance(const Shared<EnemyBullet>& bullet);

private:

	const Shared<dxe::Mesh> _bossMesh_ref = nullptr;
	std::map<int, Shared<EnemyBullet>> _bltHellsBlt_map;


	// �x�������Ŏg�p����^�C�}�[
	static std::map<Shared<EnemyBullet>, float> bullet_timers;

public:

	static int currentBulletNum;

	int bullet_count{};
	int bullet_speed{};
};