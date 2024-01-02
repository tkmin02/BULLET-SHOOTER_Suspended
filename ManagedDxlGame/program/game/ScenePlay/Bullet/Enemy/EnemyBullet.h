#pragma once
#include "../Bullet.h"
#include "../../Character/Enemy/EnemyBase.h"
#include "../../Character/Player/Player.h"

class Player;


class EnemyBullet : public Bullet
{
public:

	EnemyBullet(){}
	~EnemyBullet(){}
	EnemyBullet(const float bullet_speed) {}

	EnemyBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction) {}
	EnemyBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction, Shared<Player> player_ref) {}


public:

	Shared<dxe::Mesh> _mesh = nullptr;
	tnl::Vector3 _move_dir = { 0,0,0 };  //  �i�s����

protected:

	std::list<Shared<EnemyBullet>> _straight_bullets_e;

	Shared<Player> _player_ref;
	Shared<EnemyBase> _enemy_ref;


	tnl::Vector3 prev_pos;

public:

	float _speed;
	bool _isActive;


protected:

	float _elapsed;
	float _vx;
	float _vy;
	float _vz;

	int _num;
	float _fire_interval;    // ���ˊԊu

	float _angle;            // ���݌����Ă�������̊p�x
	float _to_player_angle;  // �v���C���[�Ƃ̊p�x��
};