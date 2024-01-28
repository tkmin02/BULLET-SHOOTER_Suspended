#include "EnemyBoss_PatchouliKnowledge.h"
#include "../../../Bullet/Enemy/BulletHell.h"
#include "../../../ScenePlay.h"



EnemyBoss_PatchouliKnowledge::EnemyBoss_PatchouliKnowledge(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(info, player, camera) {

	collide_size = { 50,50,50 };

}


void EnemyBoss_PatchouliKnowledge::SetMeshInfo() {

	_mesh = dxe::Mesh::CreateSphereMV(50);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/bossTexture/PatchouliKnowledge.jpg"));

	_mesh->pos_ = { 0, 0, 0 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}


void EnemyBoss_PatchouliKnowledge::InitBulletHellInstance() {

	_bulletHell = std::make_shared<BulletHell>(_mesh);
}


void EnemyBoss_PatchouliKnowledge::AttackPlayer(const float& delta_time) {

	if (EnemyBase::_bossHp.empty()) return;

	if (!_bulletHell) return;

	if (4 == EnemyBase::_bossHp.size() || 2 == EnemyBase::_bossHp.size()) {

		ScenePlay::_isUsingBullet_normal_patchouli = true;
		_bulletHell->ShotBulletHell_Normal_Patchouli(delta_time);
	}
	else {
		ScenePlay::_isUsingBullet_normal_patchouli = false;
	}

	if (3 == EnemyBase::_bossHp.size()) {
		ScenePlay::_isUsingBullet_metalFatigue_patchouli = true;
		_bulletHell->ShotBulletHell_MetalFatigue_Patchouli(delta_time);
	}
	else {
		ScenePlay::_isUsingBullet_metalFatigue_patchouli = false;
	}

	if (1 == EnemyBase::_bossHp.size()) {
		ScenePlay::_isUsingBullet_silentSerena_patchouli = true;
		_bulletHell->ShotBulletHell_SilentSerena_Patchouli(delta_time);
	}
	else {
		ScenePlay::_isUsingBullet_silentSerena_patchouli = false;
	}
}



void EnemyBoss_PatchouliKnowledge::DoRoutineMoves(float delta_time) {

	LookAtPlayer();

	AttackPlayer(delta_time);
}

void EnemyBoss_PatchouliKnowledge::RenderBossSpellCardName() {

	int x = 650;
	int y = 700;

	std::string spell = "Spell:";

	SetFontSize(17);
	switch (EnemyBase::_bossHp.size())
	{
	case 4:
		DrawFormatString(x, y, -1, "%sNormal", spell.c_str()); break;
	case 3:
		DrawFormatString(x, y, -1, "%sMetalFatigue", spell.c_str()); break;
	case 2:
		DrawFormatString(x, y, -1, "%sNormal", spell.c_str()); break;
	case 1:
		DrawFormatString(x, y, -1, "%sSilentSerena", spell.c_str()); break;
	}
	SetFontSize(22);
}


void EnemyBoss_PatchouliKnowledge::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);


	ShowHpGage_EnemyBoss();
	RenderBossSpellCardName();
}




bool EnemyBoss_PatchouliKnowledge::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);
	return true;
}