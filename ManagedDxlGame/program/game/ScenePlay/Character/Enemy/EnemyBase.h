#pragma once
#include "../../../DxLibEngine.h"

class Player;


class EnemyBase {
public:

	EnemyBase(){}

	float GetDistanceToPlayer();

	// �`��A�e�N�X�`���A�|�W�V�����A�X�P�[��
	virtual void SetMeshInfo() {}

	virtual bool Update(float delta_time) { return true; }

	virtual void Render(Shared<dxe::Camera> camera) {}

protected:

	// �ҋ@�A�ǐՁA�U���Ȃǂ̃p�^�[�����Ǘ������s
	virtual void DoRoutineMoves(const float& delta_time) {}

	virtual void ChasePlayer(const float delta_time) {}

	virtual void AttackPlayer(const float& delta_time) {}

	void LookAtPlayer();

	tnl::Vector3 GetRandomPosition_Mt19337() const;

public:

	Shared<Player>            _player_ref = nullptr;

	Shared<dxe::Mesh>         _mesh = nullptr;

	Shared<dxe::Camera>       _mainCamera_ref = nullptr;

public:

	tnl::Vector3 collide_size{};

	bool _isDead = false;    //�G�P�̂̎��S�t���O

	// CSV���烍�[�h-----------------------

	int            _id{};
	float          _charaMoveSpeed{};
	float          _scale{};
	std::string    _name{};
	int _MAX_HP{};
	int      _maxBulletSpawnCount{};

};