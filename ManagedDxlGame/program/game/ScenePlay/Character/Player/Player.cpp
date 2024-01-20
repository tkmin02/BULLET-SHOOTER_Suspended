#include "Player.h"
#include "../../Bullet/Player/PlayerBullet.h"
#include "../../Sky/SkyBox.h"
#include "../../ScenePlay.h"
#include "../../Camera/FreeLookCamera.h"

// CreateClone()

// 半透明のオブジェクトの描画をする時の注意

//　先に不透明なオブジェクトを全て描画してから最後に半透明のオブジェクトを描画する
//　そうでないと、オブジェクトが重なった時に半透明のオブジェクトから不透明なオブジェクトが透けて見えない
//　また、半透明なオブジェクトどうしであれば、カメラから距離が遠い順に先に描画する



Player::Player(Shared<FreeLookCamera> camera_ref) {

	_mesh = dxe::Mesh::CreateSphereMV(20, 10, 10, false);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/playerTexture.jpg"));
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
	_mesh->pos_ = { 0, 100, -300 };

	_mesh->setBlendMode(DX_BLENDMODE_ADD);
	_mesh->setAlpha(0.5f);

	collide_size = { 20, 10, 10 };

	_mainCamera_ref = camera_ref;
}



void Player::SetEnemiesListRef_ClassP(std::vector<Shared<EnemyBase>> enemies_list_ref) {

	_enemies_list_ref = enemies_list_ref;
}



void Player::ControlPlayerMove() {

	// 左方向
	if (tnl::Input::IsKeyDown(eKeys::KB_A) && !_mainCamera_ref->follow) {

		move_vel_ -= tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed();
	}

	// 右方向
	if (tnl::Input::IsKeyDown(eKeys::KB_D) && !_mainCamera_ref->follow) {

		move_vel_ += tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed();
	}


	// 上方向
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {

		move_vel_ += tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
		_mesh->pos_.z += moveSpeed;

		NormalizeCameraSpeed();
	}


	// 下方向
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			move_vel_ -= tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
			_mesh->pos_.z -= 5.0f;
		}
		else {

			move_vel_ -= tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
			_mesh->pos_.z -= moveSpeed;
		}

		NormalizeCameraSpeed();
	}
}



void Player::MoveForward(const float deltaTime) {

	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))

		_mesh->pos_ += tnl::Vector3::TransformCoord(
			{ 0,0,2 }, _mesh->rot_) * _forward_velocity * deltaTime * 200;
}



float Player::GetDistanceToEnemy(const float& e_x, const float& e_y, const float& e_z) {

	tnl::Vector3 enemy_pos = { e_x,e_y,e_z };
	tnl::Vector3 dis = enemy_pos - _mesh->pos_;

	return std::sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
}



float Player::GetAngleBtw_PlayerAndEnemy(Shared<dxe::Mesh> enemy) {

	//　外積・内積は２つのベクトルの相対角度とは関係がないので使わない

	float dx = enemy->pos_.x - _mesh->pos_.x;
	float dz = enemy->pos_.z - _mesh->pos_.z;

	// プレイヤーとエネミーの位置の相対角度を求める
	float angle = atan2(dz, dx);

	return angle;
}



const tnl::Vector3 Player::GetTargetsScreenCoordinates(const float& x, const float& y, const float& z) {

	tnl::Vector3 temp = { x,y,z };

	return temp;
}



void Player::ChangeTarget_ByMouseWheel() {

	int wheel = tnl::Input::GetMouseWheel();

	// マウスホイールの入力に応じて敵のインデックスを増減
	if (wheel > 0) {
		_enemy_index++;
		if (_enemy_index >= _enemies_list_ref.size()) {
			_enemy_index = 0;
		}
	}
	else if (wheel < 0) {
		_enemy_index--;
		if (_enemy_index < 0) {
			_enemy_index = _enemies_list_ref.size() - 1;
		}
	}
}



void Player::RenderFollowPointer()
{
	// インデックスが置かれている敵のみイテレーターで取得
	auto it = std::next(_enemies_list_ref.begin(), _enemy_index);

	if (_mainCamera_ref->isShowTargetPointer) {

		tnl::Vector3 enemy_pos = (*it)->_mesh->pos_;

		// スクリーン座標へ変換
		tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen
		(
			{ enemy_pos.x, enemy_pos.y, enemy_pos.z }
			, DXE_WINDOW_WIDTH
			, DXE_WINDOW_HEIGHT
			, _mainCamera_ref->view_
			, _mainCamera_ref->proj_
		);

		// 追従ポインター描画
		GetTargetsScreenCoordinates(enemy_pos.x, enemy_pos.y, enemy_pos.z);
		DrawCircleAA(screen_pos.x, screen_pos.y, 5, 10, GetColor(255, 0, 0), 1, 1);
	}
}


bool Player::IsEnemyInCapturableRange() {

	tnl::Vector3 player_pos = _mesh->pos_;

	for (auto it_eneList_ref = _enemies_list_ref.begin(); it_eneList_ref != _enemies_list_ref.end(); it_eneList_ref++) {

		tnl::Vector3 target_enemy_pos = (*it_eneList_ref)->_mesh->pos_;
		float dis_player_enemy = (target_enemy_pos - player_pos).length();
		if (dis_player_enemy < 500) {
			return true;
		}
	}
	return false;
}


void Player::ActivateDarkSoulsCamera() {

	tnl::Vector3 player_pos = _mesh->pos_;

	for (auto it_eneList_ref = _enemies_list_ref.begin(); it_eneList_ref != _enemies_list_ref.end(); it_eneList_ref++) {

		tnl::Vector3 target_enemy_pos = (*it_eneList_ref)->_mesh->pos_;
		float dis_player_enemy = (target_enemy_pos - player_pos).length();

		if (_mainCamera_ref->follow) {

			// 追従ポインターON（描画）
			_mainCamera_ref->isShowTargetPointer = true;

			ChangeTarget_ByMouseWheel();
			RenderFollowPointer();

			tnl::Vector3 tmp{};
			tmp.y = player_pos.y - 70;

			// カメラをプレイヤーと敵の中間地点に固定
			_mainCamera_ref->target_ = (tmp + target_enemy_pos) / 2;

			tnl::Vector3 cameraOffset = { 0, 0, -200 };
			tnl::Vector3 cameraPos = player_pos + cameraOffset;
			// カメラの位置 = プレイヤー座標 + (normalized(プレイヤー座標 - 敵座標) * カメラとプレイヤーの差分)
			// ただし、単純にプレイヤーの座標を使うとプレイヤーとエネミーが重なってしまうため、差分を使う


			tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
			tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);

			tnl::Vector3 local_axis_x = tnl::Vector3::Cross({ 0,1,0 }, xz);
			q *= tnl::Quaternion::RotationAxis(local_axis_x, _mainCamera_ref->axis_x_angle_);

			_mesh->rot_ = tnl::Quaternion::LookAt(player_pos, target_enemy_pos, local_axis_x);

			//左方向
			if (tnl::Input::IsKeyDown(eKeys::KB_A)) {

				tnl::Vector3 new_pos = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, 0, -150 }, q);
				new_pos.y = _mesh->pos_.y;

				_mesh->pos_ = new_pos;
				_mainCamera_ref->axis_y_angle_ += tnl::ToRadian(2);
			}

			// 右方向
			if (tnl::Input::IsKeyDown(eKeys::KB_D)) {

				tnl::Vector3 new_pos = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, 0, -150 }, q);
				new_pos.y = _mesh->pos_.y;

				_mesh->pos_ = new_pos;
				_mainCamera_ref->axis_y_angle_ -= tnl::ToRadian(2);
			}


			// カメラの動きの遅延処理
			tnl::Vector3 fix_pos = player_pos + tnl::Vector3::TransformCoord({ _player_behind_cameraX, 100, -150 }, _mesh->rot_);
			_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;
		}
	}

	ControlCameraWithoutEnemyFocus(player_pos);
}




void Player::ControlCameraWithoutEnemyFocus(tnl::Vector3& player_pos)
{
	tnl::Vector3 _camera_offset = { 0, -50, 20 };

	// 敵にカメラを固定しない場合
	_mainCamera_ref->target_ = player_pos;
	_mainCamera_ref->target_ -= _camera_offset;

	ControlRotationByMouse();

	// カメラの動きの遅延処理
	tnl::Vector3 fix_pos = player_pos + tnl::Vector3::TransformCoord({ 0, 100, -150 }, _mesh->rot_);
	_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;

	// 追従ポインターOFF
	_mainCamera_ref->isShowTargetPointer = false;
}




void Player::NormalizeCameraSpeed() {

	tnl::Vector3 zero = { 0,0,0 };

	if ((move_vel_ - zero).length() > 0.0f) {

		// ベクトル正規化
		move_vel_ = move_vel_.Normalize(move_vel_) * 4;
	}
}




void Player::ControlMainCameraPos(const CameraPos enum_camera_pos) {

	switch (enum_camera_pos)
	{
	case CameraPos::DIR_RIGHT:
		_mainCamera_ref->pos_.x -= moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_LEFT:
		_mainCamera_ref->pos_.x += moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_UP:
		_mainCamera_ref->pos_.z -= moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_DOWN:
		_mainCamera_ref->pos_.z += moveSpeed + camera_pos_offset;

		break;
	default:
		break;
	}
}



void Player::ControlRotationByMouse() {


	if (!_mainCamera_ref->follow) {

		tnl::Vector3 vel = tnl::Input::GetMouseVelocity();

		// 左右視点
		rot_y_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(vel.x * 0.05f));

		// 上下視点
		tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_y_);
		rot_x_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Cross({ 0, 1, 0 }, forward), tnl::ToRadian(vel.y * 0.01f));
	}
}



void Player::ShotPlayerBullet() {

	tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;

		_straight_bullets_p.emplace_back(std::make_shared<PlayerBullet>(spawn_pos, move_dir, _player_ref));
	}
}



void Player::AdjustPlayerVelocity() {

	// Time.deltaTimeのようなもの。これがないとプレイヤーが吹っ飛ぶ
	tnl::EasyAdjustObjectVelocity(centroid_radius_, mass_, friction_, past_move_vel_, move_vel_, center_of_gravity_);

	_mesh->pos_ += move_vel_;

	if (center_of_gravity_.length() > FLT_EPSILON) {
		// 重心位置を利用して傾いてほしいアッパーベクトルを作成
		tnl::Vector3 upper = tnl::Vector3::Normalize({ center_of_gravity_.x, centroid_radius_, center_of_gravity_.z });
		// 傾きの角度を計算
		float angle = upper.angle({ 0, 1, 0 });
		// 傾きベクトルと真上ベクトルの外積から回転軸を計算し、傾き角度を調整して回転クォータニオンを作成
		rot_xz_ = tnl::Quaternion::RotationAxis(tnl::Vector3::Cross(upper, { 0, 1, 0 }), -(angle * 0.2f));
	}


	// 最終的な姿勢
	_mesh->rot_ = rot_y_ * rot_xz_;
	// ControlRotationByMouse で上下視点も使用する場合は↓を使う
	_mesh->rot_ = rot_y_ * rot_x_ * rot_xz_;
}



void Player::Update(float delta_time) {

	ControlPlayerMove();

	ActivateDarkSoulsCamera();

	// 右マウスが押されたら、カメラを敵に固定するフラグを反転
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT) && IsEnemyInCapturableRange()) {
		_mainCamera_ref->follow = !_mainCamera_ref->follow;
	}


	_mainCamera_ref->Update(delta_time);
	_mainCamera_ref->ControlFreeLookCamera(_mainCamera_ref, _mesh);

	MoveForward(delta_time);


	ShotPlayerBullet();


	AdjustPlayerVelocity();

	UpdateStraightBullet(delta_time);
}



void Player::UpdateStraightBullet(float delta_time)
{
	auto it_blt = _straight_bullets_p.begin();

	while (it_blt != _straight_bullets_p.end()) {

		(*it_blt)->Update(delta_time);

		if (!(*it_blt)->_isActive) {
			it_blt = _straight_bullets_p.erase(it_blt);
			continue;
		}
		it_blt++;
	}
}



void Player::Render(Shared<FreeLookCamera> camera) {

	_mesh->render(camera);

	for (auto blt : _straight_bullets_p) blt->Render(camera);
}