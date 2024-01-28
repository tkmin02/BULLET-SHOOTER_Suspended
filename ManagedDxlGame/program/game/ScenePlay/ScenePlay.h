#pragma once
#include "../DxLibEngine.h"
#include "../../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"


class Player;
class SkyBox;
class HeightMap;
class Collision;
class EnemyBase;
class EnemyManager;
class Score;
class FreeLookCamera;
class EnemyBullet;
class BulletHellFactory;

struct SpawnedBossBulletInfo;

class ScenePlay : public SceneBase
{
public:

	ScenePlay(){}
	ScenePlay(std::string selected_difficulty, int stage);

	void MoveToNextStage(int stage, std::string difficulty);


private:

	void DestroyFirstStageBulletHellLists();
	void RenderFirstStageBulletHellLists();
	void UpdateFirstStageBulletHellLists();


	void RenderEnemyRadarOnMiniMap();
	void Render() override;
	void Update(float deltaTime) override;


public:

	static Shared<dxe::Particle> _weather_particle;

private:

	Shared<FreeLookCamera>_mainCamera = nullptr;

	Shared<Player>        _player = nullptr;

	Shared<EnemyManager>  _enemyManager = nullptr;

	Shared<SkyBox>        _skyBox = nullptr;

	Shared<HeightMap>     _heightMap = nullptr;

	Shared<Collision>     _collision = nullptr;

	Shared<Score>         _score = nullptr;
	 
	Shared<dxe::ScreenEffect> _screen_effect = nullptr;

	Shared<BulletHellFactory> _bltHellFactory = nullptr;

public:

	static std::list<Shared<EnemyBullet>> _bullet_normal_patchouli;
	static std::list<Shared<EnemyBullet>> _bullet_silentSerena_patchouli;
	static std::list<Shared<EnemyBullet>> _bullet_metalFatigue_patchouli;

public:
	static std::unordered_map<int, SpawnedBossBulletInfo> _BLTINFO_T_NORMAL_PATCHOULI;
	static std::unordered_map<int, SpawnedBossBulletInfo> _BLTINFO_T_METALFATIGUE_PATCHOULI;
	static std::unordered_map<int, SpawnedBossBulletInfo> _BLTINFO_T_SILENTSERENA_PATCHOULI;

	static bool _isUsingBullet_normal_patchouli;
	static bool _isUsingBullet_metalFatigue_patchouli;
	static bool _isUsingBullet_silentSerena_patchouli;


private:

	int miniMap_hdl{};

	int _STAGE_ID;

	tnl::Vector2i miniMap_center_pos = { 120,600 };
};