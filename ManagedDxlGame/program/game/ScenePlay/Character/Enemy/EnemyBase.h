#pragma once
#include "../../../DxLibEngine.h"
#include "../Player/Player.h"
#include "../../../Loader/EnemyLoader.h"
#include "../../Bullet/Bullet.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../EnemyMove/EnemyMover.h"

class EnemyMover;
class EnemyBullet;
class StraightBullet;

class EnemyBase : public CollisionObject
{

public:

	EnemyBase() {}

	EnemyBase(std::list <Shared<EnemyBase>> _enemyList) { _enemy_list_ref = _enemyList; }

	EnemyBase(EnemyInfo& info) {}

	EnemyBase(const EnemyInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	virtual ~EnemyBase() = default;

	virtual bool Update(float delta_time);

	virtual void Render(Shared<dxe::Camera> _mainCamera) {};

	void Initialize();

	// EnemyMover �I�u�W�F�N�g����
	void NewEnemyMover() { _mover = std::make_shared<EnemyMover>(); }

	// �Q�b�^�[
	float GetDistanceToPlayer();

	virtual float GetRandomValue_Mt19337() const { return 0.0f; }

	int GetCounter() const { return _elapsed; }

	float getSpeed() const { return _speed; }

	float getAngle() const { return _angle; }

	int   getMovePatternID() const { return _move_pattern_id; }

	//�@�Z�b�^�[
	void  setAngle(float angle) { _angle = angle; }

	// �G�̍s���p�^�[��������
	void InitEnemyMove();

protected:

	// �`��A�e�N�X�`���A�|�W�V�����A�X�P�[��
	virtual void SetMeshInfo() {};

	// ����
	virtual void Clone() {}


	// �v���C���[�֏ƎˁA�ǐՂȂ�
	virtual void ShotStraightBullet() {};

	virtual std::list<Shared<StraightBullet>> InitStraightBullet() { return _straight_bullets_e; }


	// �v���C���[�֏ƎˁA�p�x�����t���Œǐ�
	virtual void ShotHomingBullet() {};

	virtual tnl::Vector3 CalcVecFromAngle(float angle) { return _mesh->pos_; };

	virtual float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) { return 0; };

	virtual void LookAtPlayer(const float delta_time) {};

public:

	Shared<dxe::Mesh>       _mesh = nullptr;

protected:

	std::list<Shared<StraightBullet>> _straight_bullets_e;
	std::list <Shared<EnemyBase>> _enemy_list_ref;

	// ScenePlay�̃����o�ϐ��Q�ƃ|�C���^	
	Shared<Player>        _player_ref = nullptr;
	Shared<dxe::Camera>   _camera_ref = nullptr;

	Shared<EnemyMover> _mover = nullptr;

	// EnemyLoader.h����̎Q��
	EnemyInfo        _enemyInfo_ref;


public:

	bool _isDead = false;    //�G�P�̂̎��S�t���O
	bool _isAllDead = false; //�G�N���X(�ő吶������)�̎��S�t���O
	bool _canShot = false;   //�e�����Ă�悤�ɂȂ�����

	// CSV���烍�[�h-----------------------
	int           _id{};
	int           _hp{};
	float      _scale{};
	std::string _name{};
	// ------------------------------------
		
protected:

	int        _score{};
	int        _elapsed{};
	int        _life_time_duration{};
	int        _move_pattern_id{};  //�ړ��p�^�[��

	float      _speed{};
	float      _angle{}; // �������g�̌��݌����Ă�������̊p�x
	float      _angle_to_player {}; // �����ƃv���C���[�̊p�x����

	bool addedRandVal_posX = false;

	int _int_time{};  // �o������

	int _stop_time{}; // ��~����

	int _shot_time{}; // ���b�Ԕ��˂������邩

	int shot_count{}; // �e���łĂ�悤�ɂȂ��Ă���̃J�E���g

	int _life_timer{}; // �������Ɏ��ԃJ�E���g���J�n���A�����𒴂��������

	int _life_time_limit{}; // �G�̎����B�^�C�}�[�����̒l�𒴂�����G������
};