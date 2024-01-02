#pragma once
#include "../Bullet.h"

class Player;

class PlayerBullet : public Bullet
{
public:

	PlayerBullet() {}
	PlayerBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction, Shared<Player> player_ref);


	void Update(float delta_time) override;
	void Render(Shared<dxe::Camera> _mainCamera) override;

	Shared<dxe::Mesh> _mesh = nullptr;
	Shared<Player> _player_ref = nullptr;

	tnl::Vector3 _move_dir = { 0,0,0 };
	tnl::Vector3 _spawn_pos = { 0, 0, -250 };

	tnl::Vector3 prev_pos;


	bool _isActive;
	float _elapsed{};
	float _speed{};
};