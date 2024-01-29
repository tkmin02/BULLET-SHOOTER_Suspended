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
		// �p�`�����[
		Normal_Patchouli,
		MetalFatigue_Patchouli,
		SilentSerena_Patchouli,
		// �`���m
		Normal_Cirno,
		IcicleFall_Cirno,
		Perfect_Freeze_Cirno,
		// �z�K�q
		KeroChan_StandsFirm_AgainstTheStorm_Suwako,
	};

public:

	BulletHell() {}
	BulletHell(const Shared<dxe::Mesh>& bossMesh);

	// �X�e�[�W1�{�X�i�p�`�����[�j-------------------------------------
	void ShotBulletHell_Normal_Patchouli(const float& delta_time);
	void ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time);
	void ShotBulletHell_SilentSerena_Patchouli(const float& delta_time);
	// �X�e�[�W2�{�X�i�`���m�j---------------------------------------------
	void ShotBulletHell_Normal_Cirno(const float& delta_time);
	void ShotBulletHell_IcicleFall_Cirno(const float& delta_time);
	void ShotBulletHell_PerfectFreeze_Cirno(const float& delta_time);
	// �X�e�[�W3�{�X�i�z�K�q�j---------------------------------------------
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