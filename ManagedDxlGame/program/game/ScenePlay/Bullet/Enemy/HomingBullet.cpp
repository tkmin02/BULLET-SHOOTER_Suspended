#include "HomingBullet.h"
#include "../../../DxLibEngine.h"


HomingBullet::HomingBullet(Shared<HomingBullet> straightBullet) {

	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/purple.jpg"));
}



HomingBullet::HomingBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir, const Shared<Player>& player, const float& speed) {

	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/purple.jpg"));
	_mesh->pos_ = spawn_pos;
	_move_dir = move_dir;

	_speed = speed;
	_player_ref = player;
}



void HomingBullet::Render(Shared<dxe::Camera> _mainCamera) {
	_mesh->render(_mainCamera);
}



void HomingBullet::Update(float delta_time) {

	// ’e‚ÌŽõ–½‚Í‹——£‚ÅŠÇ—
	static tnl::Vector3 start = _mesh->pos_;


	float dx = _mesh->pos_.x - start.x;
	float dy = _mesh->pos_.y - start.y;
	float dz = _mesh->pos_.z - start.z;

	// ‹——£
	float current_distance = sqrt(dx * dx + dy * dy + dz * dz);
	//float current_distance = (_mesh->pos_ - start).length();  © ‚±‚ÌŒvŽZ‚Å‚àOK

	tnl::Vector3 player_dir = _mesh->pos_ - _player_ref->_mesh->pos_;
	player_dir.normalize();

	// Šp“x
	float angle = acos(_move_dir.dot(player_dir));

	if (angle < (90 * tnl::PI) / 180)
	{
		_move_dir = player_dir;
		_move_dir.normalize();
	}

	_mesh->pos_ += _move_dir * delta_time * _speed;


	// ”ò‹——£‚ª600‚ð’´‚¦‚½‚çÁ‹Ž
	if (abs(current_distance) > 600) _isActive = false;
}