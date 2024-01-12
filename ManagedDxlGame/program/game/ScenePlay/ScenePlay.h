#pragma once
#include "../DxLibEngine.h"
#include "../../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"
#include "../Loader/CsvLoader.h"
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

	ScenePlay(){}
	ScenePlay(std::string selected_difficulty, int stage);

	void MoveNextStage(int stage);

private:

	void RenderEnemyRadarOnMiniMap();
	void Render() override;
	void Update(float deltaTime) override;

private:

	Shared<dxe::Camera> _mainCamera = nullptr;

	Shared<Player> _player = nullptr;

	Shared<EnemyManager> _enemyManager = nullptr;

	Shared<SkyBox> _skyBox = nullptr;

	Shared<HeightMap> _heightMap = nullptr;

	Shared<Collision> _collision = nullptr;

private:

	int miniMap_hdl{};
	const std::string _DIFFICULTY{};

	tnl::Vector2i miniMap_center_pos = { 120,600 };

};