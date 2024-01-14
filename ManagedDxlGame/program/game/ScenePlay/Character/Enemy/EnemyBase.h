#pragma once
#include <chrono>
#include "../../../DxLibEngine.h"
#include "../Player/Player.h"
#include "../../../Loader/CsvLoader.h"
#include "../../Bullet/Bullet.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../EnemyMove/EnemyMover.h"

class EnemyMover;
class EnemyBullet;
class StraightBullet;

class EnemyBase : public CollisionObject
{
public:

	//-
	EnemyBase() {}

	EnemyBase(std::vector<Shared<EnemyBase>>& enemyList) {}

	EnemyBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	EnemyBase(const EnemyBossInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	virtual ~EnemyBase() = default;

	virtual bool Update(float delta_time);

	virtual void Render(Shared<dxe::Camera> _mainCamera) {};

	void Initialize();

	// EnemyMover �I�u�W�F�N�g����
	void NewEnemyMover() { _mover = std::make_shared<EnemyMover>(); }

	// �Q�b�^�[
	float GetDistanceToPlayer();

	tnl::Vector3 GetRandomPosition_Mt19337() const;

	// �G�̍s���p�^�[��������
	void InitEnemyMove();

	void DecreaseHP(int damage);

	void DecreaseBossHP(int damage);


	virtual bool ShowHpGage_EnemyZako();

	virtual bool ShowHpGage_EnemyBoss();

protected:

	// �e�n--------------------------------------------------------------
	virtual void UpdateStraightBullet(const float delta_time) {}
	// �v���C���[�֏ƎˁA�ǐՂȂ�
	virtual void ShotStraightBullet(std::list<Shared<EnemyBullet>> bullet) {};

	virtual void UpdateHomingBullet(const float delta_time) {}

	virtual void InitHomingBullet() {}

	// �`��A�e�N�X�`���A�|�W�V�����A�X�P�[��
	virtual void SetMeshInfo() {};

	// ����
	virtual void Clone() {}

	virtual void InitStraightBullet() {}

	// �v���C���[�֏ƎˁA�p�x�����t���Œǐ�
	virtual void ShotHomingBullet() {};

	virtual tnl::Vector3 CalcVecFromAngle(float angle) { return _mesh->pos_; };

	virtual float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) { return 0; };


	// �ҋ@�A�ǐՁA�U���Ȃǂ̃p�^�[�����Ǘ������s
	virtual void DoRoutineMoves(float delta_time) {}

	virtual void ChasePlayer(const float delta_time) {}

	virtual void AttackPlayer(float delta_time) {}

	void LookAtPlayer();

	void RenderBossName();

	void RenderBossRemainLife();

public:

	Shared<dxe::Mesh>       _mesh = nullptr;

protected:

	std::list <Shared<EnemyBase>> _enemy_list_ref;

	// ScenePlay�̃����o�ϐ��Q�ƃ|�C���^	
	Shared<Player>        _player_ref = nullptr;
	Shared<dxe::Camera>   _mainCamera_ref = nullptr;

	Shared<EnemyMover> _mover = nullptr;

public:

	bool _isDead = false;    //�G�P�̂̎��S�t���O
	bool _isAllDead = false; //�G�N���X(�ő吶������)�̎��S�t���O
	bool _canShotStraightBullet = true;   // ���s�e�����Ă��Ԃ�
	bool _canShotHomingBullet = true;   // ���s�e�����Ă�悤�ɂȂ�����


	// CSV���烍�[�h-----------------------

	int            _id{};
	int            _maxBulletSpawnCount{};
	int            _maxTotalEnemySpawnCount{};
	int            _hp{};
	std::deque<int>_bossHp{};
	float          _charaMoveSpeed{};
	float          _scale{};
	std::string    _name{};
	int _MAX_HP{};

	// ------------------------------------

protected:

	int        _move_pattern_id{};  //�ړ��p�^�[��

	int _life_timer{}; // �������Ɏ��ԃJ�E���g���J�n���A�����𒴂��������

	int _life_time_limit{}; // �G�̎����B�^�C�}�[�����̒l�𒴂�����G������

	// �e�n--------------------------------------------------------------
	unsigned int last_shot_time_straight_blt;
	unsigned int last_shot_time_homing_blt;

private:

	std::stack<std::deque<int>> _remaining_life_indicator;

};