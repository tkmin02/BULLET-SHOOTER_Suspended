#pragma once
#include <vector>
#include "../../../DxLibEngine.h"
#include "../../Character/Enemy/EnemyZakoBase.h"
#include "../../Character/Enemy/EnemyBossBase.h"

class PlayerBullet;
class EnemyZakoBase;
class EnemyBossBase;
class FreeLookCamera;

class Player
{
public:

	Player() {}

	explicit Player(Shared<FreeLookCamera> camera_ref);

	const tnl::Vector3 GetPos() const { return _mesh->pos_; }
	void SetPos(const tnl::Vector3 pos) { _mesh->pos_ = pos; }

	// 管理するエネミーのリストの参照用
	void SetEnemyZakoListRef(const std::vector<Shared<EnemyZakoBase>>& enemy_list_ref);
	void SetEnemyBossListRef(const std::vector<Shared<EnemyBossBase>>& enemyBoss_ref);
	void EraseEnemyZakoListRef(Shared<EnemyZakoBase>& enemy_list_ref);
	void EraseEnemyBossListRef(Shared<EnemyBossBase>& enemyBoss_ref);


	// プレイヤーの実体はScenePlayクラスにある
	void SetPlayerRef(Shared<Player> player_ref) { _player_ref = player_ref; }

	void DecreaseHP(int damage);

	void Update(float delta_time);
	void Render(Shared<FreeLookCamera> playerCamera);

private:

	// プレイヤー関係
	void ControlPlayerMove(const float delta_time);
	void AdjustPlayerVelocity();
	void ControlRotationByPadOrMouse();
	void RenderPlayerHp();

	// 敵関係
	const tnl::Vector3 GetTargetsScreenCoordinates(const float& x, const float& y, const float& z);
	void ChangeTarget_ByMouseWheel();
	void RenderFollowPointer();
	bool IsEnemyInCapturableRange();

	// カメラ関係
	void ActivateDarkSoulsCamera();
	void ControlCameraWithoutEnemyFocus();
	void NormalizeCameraSpeed(const float speed);
	void UpdateStraightBullet(float delta_time);
	void ShotPlayerBullet();

public:

	Shared<dxe::Mesh> _mesh = nullptr;
	std::list<Shared<PlayerBullet>> _straight_bullets_p;

	tnl::Vector3 collide_size{};

private:

	Shared<Player> _player_ref = nullptr;
	Shared<FreeLookCamera> _mainCamera_ref = nullptr;

	Shared<EnemyZakoBase> _enemyZako_ref = nullptr;
	Shared<EnemyBossBase> _enemyBoss_ref = nullptr;
	std::vector<Shared<EnemyZakoBase>> _enemyZako_list_ref{};
	std::vector<Shared<EnemyBossBase>> _enemyBoss_list_ref{};


	int   _hp{};
	int   _MAX_HP{};
	int   _enemy_index{};
	float _player_behind_cameraX{};

	float _forward_velocity = 1.0f;

	bool _isDead{};
	bool _isInvincible{};
	float _invincibleTime = 1.5f;
	float _invincibleRestTime{};

	float _moveSpeed = 0.4f;

	float centroid_radius_ = 100; // 重心
	float mass_ = 100;            // 質量
	float friction_ = 0.6f;       // 摩擦
	tnl::Vector3 move_vel_{};
	tnl::Vector3 past_move_vel_{};
	tnl::Vector3 center_of_gravity_{};
	tnl::Quaternion rot_y_{};
	tnl::Quaternion rot_x_{};
	tnl::Quaternion rot_xz_{};
};