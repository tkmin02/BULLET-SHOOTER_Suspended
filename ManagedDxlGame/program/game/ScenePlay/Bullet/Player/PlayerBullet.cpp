#include "PlayerBullet.h"
#include "../../Character/Player/Player.h"


PlayerBullet::PlayerBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction, Shared<Player> player_ref)  {

	_player_ref = player_ref;
	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/red1.bmp"));
	_mesh->pos_ = spawn_pos;
	_move_dir = direction; 
	_speed = 1000.0f;
}


void PlayerBullet::Render(Shared<dxe::Camera> _mainCamera) {

	_mesh->render(_mainCamera);
}


void PlayerBullet::Update(float delta_time) {

	static tnl::Vector3 start = _mesh->pos_;

	_mesh->pos_ += _move_dir * delta_time * _speed;

	float dx = _mesh->pos_.x - start.x;
	float dy = _mesh->pos_.y - start.y;
	float dz = _mesh->pos_.z - start.z;

	float current_distance = sqrt(dx * dx + dy * dy + dz * dz);

	// ”ò‹——£‚ª900‚ð’´‚¦‚½‚çÁ‹Ž
	if (abs(current_distance) > 900) _isActive = false;	
}