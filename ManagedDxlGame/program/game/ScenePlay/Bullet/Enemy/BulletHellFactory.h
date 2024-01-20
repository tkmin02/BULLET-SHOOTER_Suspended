#pragma once

class BulletHell;

// ����̒e���p�^�[���𐶐�

class BulletHellFactory
{
public:

	BulletHellFactory();

	void InitBulletHellInfo();

	std::list<Shared<EnemyBullet>> CreateBulletHell(const BulletHell::TYPE type);

	Shared<EnemyBullet> ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map,int id);

	Shared<EnemyBullet> GetBulletHellsBullet(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

private:

	//// <summary>
	//  �� (�p�`�����[��p)
	// �~�`�A�����˂ƁA�����_���ɂ�����藎���Ă���e��g�ݍ��킹���e��
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_SilentSerena();

	//// <summary>
	//  �� (�`���m��p)
	// 1.�S�����΂�T���V���b�g������
	// 2.�t���[�Y�A�e���~�߂Ĕ�������
	// 3.���@�ˑ����ꂽ�W�����V���b�g��A���ł���
	// 4.�~�߂Ă����e��S�����œ������n�߂�
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_PerfectFreeze();

	//// <summary>
	//�@�� (�z�K�q��p)
	//�@1.��Ɍ�������8way�e������
	//�@2.���X�ɉ������ɉ������Ă���
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();

private:

	Shared<CsvLoader> _csvLoader = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};

	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;
};