#include "StraightBullet.h"
#include "EnemyBullet.h"



StraightBullet::StraightBullet(Shared<StraightBullet> straightBullet) {


	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/enemyshot.png"));
}



StraightBullet::StraightBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir, const Shared<Player>& player, const float& speed) {

	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/enemyshot.png"));
	_mesh->pos_ = spawn_pos;
	_move_dir = move_dir;

	_speed = speed;
	_player_ref = player;
}



 void StraightBullet::Render(Shared<dxe::Camera> _mainCamera) {
	_mesh->render(_mainCamera);
}


void StraightBullet::Update(float delta_time) {

	// ’e‚ÌŽõ–½‚Í‹——£‚ÅŠÇ—
	static tnl::Vector3 start = _mesh->pos_;

	_mesh->pos_ += _move_dir * delta_time * _speed;

	float dx = _mesh->pos_.x - start.x;
	float dy = _mesh->pos_.y - start.y;
	float dz = _mesh->pos_.z - start.z;

	float current_distance = sqrt(dx * dx + dy * dy + dz * dz);

	// ”ò‹——£‚ª1000‚ð’´‚¦‚½‚çÁ‹Ž
	if (abs(current_distance) > 600) {

		_isActive = false;
	}
}