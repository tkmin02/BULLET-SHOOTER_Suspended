#pragma once
#include "../DxLibEngine.h"
#include "../../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"
#include "../Loader/EnemyLoader.h"
#include "../Manager/Enemy/EnemyManager.h"
#include "Collision/Collision.h"

class SceneBase;
class Player;
class SkyBox;
class HeightMap;
class EnemyBase;
class EnemyManager;


class ScenePlay : public SceneBase
{
public:

	ScenePlay();

private:

	int miniMap_hdl{};

	tnl::Vector2i miniMap_center_pos = { 120,600 };


	// ïœêî-----------------------------------
	Shared<dxe::Camera> _mainCamera = nullptr;

	Shared<Player> _player = nullptr;

	Shared<EnemyManager> _enemyManager = nullptr;

	Shared<SkyBox> _skyBox = nullptr;

	Shared<HeightMap> _heightMap = nullptr;

	Shared<Collision> _collision = nullptr;

	// ä÷êî-----------------------------------

	void RenderEnemyRadarOnMiniMap();
	void Render() override;
	void Update(float deltaTime) override;
};