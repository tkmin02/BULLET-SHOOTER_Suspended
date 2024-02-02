#pragma once
#include "../../../DxLibEngine.h"

class PlayerBullet;
class EnemyZakoBase;
class EnemyBossBase;
class FreeLookCamera;

class Player
{
public:

	Player() {}
	explicit Player(Shared<FreeLookCamera> camera_ref);

	// ÉvÉåÉCÉÑÅ[ä÷åW
	void SetPlayerRef(Shared<Player> player_ref) { _player_ref = player_ref; }
	void SetBombCount(const int count) { _current_bomb_stock_count = count; }
	bool DecreaseHP(int damage);
	const tnl::Vector3 GetPos() const { return _mesh->pos_; }
	void SetPos(const tnl::Vector3 pos) { _mesh->pos_ = pos; }

	// ìGä÷åW
	void SetEnemyZakoListRef(const std::vector<Shared<EnemyZakoBase>>& enemy_list_ref);
	void SetEnemyBossListRef(const std::vector<Shared<EnemyBossBase>>& enemyBoss_ref);
	void EraseEnemyZakoListRef(Shared<EnemyZakoBase>& enemy_list_ref);
	void EraseEnemyBossListRef(Shared<EnemyBossBase>& enemyBoss_ref);

	void Update(float delta_time);
	void Render(Shared<FreeLookCamera> playerCamera);

private:

	// ÉvÉåÉCÉÑÅ[ä÷åW
	void ControlPlayerMove(const float delta_time);
	void AdjustPlayerVelocity();
	void ControlRotationByPadOrMouse();
	void RenderPlayerHp();
	void InvincibleTime(const float delta_time);
	void ShotPlayerBullet();
	void UseBomb();
	void ValidateBombEffect();
	void InvalidateBombEffect(const float delta_time);
	void RenderBombRemainCount();

	// ìGä÷åW
	const tnl::Vector3 GetTargetsScreenCoordinates(const float& x, const float& y, const float& z);
	void ChangeTarget_ByMouseWheel();
	void RenderFollowPointer();
	bool IsEnemyInCapturableRange();

	// ÉJÉÅÉâä÷åW
	void ActivateDarkSoulsCamera();
	void ControlCameraWithoutEnemyFocus();
	void NormalizeCameraSpeed(const float speed);
	void UpdateStraightBullet(float delta_time);

public:

	Shared<dxe::Mesh> _mesh = nullptr;
	std::list<Shared<PlayerBullet>> _straight_bullets_p;

	static Shared<dxe::Particle> _bomb_particle;

private:

	Shared<Player> _player_ref = nullptr;
	Shared<FreeLookCamera> _mainCamera_ref = nullptr;

	Shared<EnemyZakoBase> _enemyZako_ref = nullptr;
	Shared<EnemyBossBase> _enemyBoss_ref = nullptr;

	std::vector<Shared<EnemyZakoBase>> _enemyZako_list_ref{};
	std::vector<Shared<EnemyBossBase>> _enemyBoss_list_ref{};

public:

	tnl::Vector3 collide_size{};
	static bool _isInvincible;
	static int  _current_bomb_stock_count;

private:

	int   _hp{};
	int   _MAX_HP{};
	int   _enemy_index{};
	float _player_behind_cameraX{};

	float _forward_velocity = 1.0f;

	bool _isDead{};

	static float _invincible_timer;
	const float _INVINCIBLE_TIME_LIMIT = 3.0f;

	static float _bomb_timer;

	float _moveSpeed = 0.4f;

	float centroid_radius_ = 100; // èdêS
	float mass_ = 100;            // éøó 
	float friction_ = 0.6f;       // ñÄéC
	tnl::Vector3 move_vel_{};
	tnl::Vector3 past_move_vel_{};
	tnl::Vector3 center_of_gravity_{};
	tnl::Quaternion rot_y_{};
	tnl::Quaternion rot_x_{};
	tnl::Quaternion rot_xz_{};
};