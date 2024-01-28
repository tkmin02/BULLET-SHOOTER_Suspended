#pragma once

class BulletHell;
class EnemyManager;

// ����̒e���p�^�[���𐶐�

class BulletHellFactory
{
public:

	BulletHellFactory(){}

	explicit BulletHellFactory(const Shared<EnemyManager>& enemyManager);

	void InitBulletHellInfo();

	std::list<Shared<EnemyBullet>> CreateBulletHell(const BulletHell::TYPE type);

	Shared<EnemyBullet> ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

	Shared<EnemyBullet> GetBulletHellsBullet(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id);

private:

	//// <summary>
    //  �� (�p�`�����[��p)
    // 1.�{�X�̎��͂�4�̋���Ȓe�𐶐�
	// 2.���̒e���璼���Ɍ��������
	// 3.����������Ȃ��獶��]
	// 4.�{�X�̎��͂ɐV����4�̋���Ȓe�𐶐�
	// 5.�����悤�ɒe���璼���Ɍ���������A���x�͉E��]
	// 6.����]�����Ă���e�ƌ���������
	// 7.�E��]�����Ă���e�ƌ���������
	// 8.�l�������ɂS�A���Œe�𔭎�
	// 9.����]�A�E��]�̋Z�ɍ��킹�A�l�������ɂS�A���Œe�𔭎�
    //// </summary>
    std::list<Shared<EnemyBullet>> CreateBulletHell_Normal_Patchouli();


	//// <summary>
	//  �� (�p�`�����[��p)
	// �~�`�A�����˂ƁA�����_���ɂ������߂Â��Ă���e��g�ݍ��킹���e��
	//// </summary>
	std::list<Shared<EnemyBullet>> CreateBulletHell_SilentSerena_Patchouli();


	//// <summary>
    //  �� (�p�`�����[��p)
    // �~���8way�e���W�J����A�r���ł��ꂼ�ꂪ8way�e�ɑ�����B
    //// </summary>
    std::list<Shared<EnemyBullet>> CreateBulletHell_MetalFatigue_Patchouli();

	//// <summary>
	/// ���@CreateBulletHell_MetalFatigue_Patchouli�֐��Ŏg�p����e���������W�b�N�̊֐���
	/// </summary>
	/// <param name="split_one_into_eight_WAVE1"></param>
	/// <param name="split_one_into_eight_bullet"></param>
	//// <param name="enemyBullet"></param>
	void InitSplitOneIntoEightBullet(int split_one_into_eight_WAVE1, Shared<EnemyBullet>& split_one_into_eight_bullet, std::list<Shared<EnemyBullet>>& enemyBullet, const std::string& wave);



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

	Shared<BulletHell> _bulletHell = nullptr;

	Shared<EnemyManager> _enemyManager = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};

	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;


};