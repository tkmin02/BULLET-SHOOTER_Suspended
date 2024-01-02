#include "PlayerBullet.h"
#include "../../Character/Player/Player.h"



PlayerBullet::PlayerBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction, Shared<Player> player_ref)  {

	_player_ref = player_ref;
	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/red1.bmp"));
	_mesh->pos_ = spawn_pos;
	_move_dir = direction; 
}


void PlayerBullet::Render(Shared<dxe::Camera> _mainCamera) {


	_mesh->render(_mainCamera);
}


void PlayerBullet::Update(float delta_time) {

	_move_dir;
	prev_pos = _mesh->pos_;

	_elapsed += delta_time;

	_mesh->pos_ += _move_dir * 30;
	if (_mesh->pos_.z > 1000) _isActive = false;
}