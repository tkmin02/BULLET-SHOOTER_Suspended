#pragma once

class BulletHell;
class EnemyManager;

// �p�`�����[�i�m�[�}���j
constexpr int _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI = 8;
constexpr int _EVERYDIRECTION_BULLETCOUNT_T_NORMAL_PATCHOULI = 192;
// �p�`�����[�i���^���E�t�@�e�B�[�O�j
constexpr int _EVERYDIRECTION_BULLETCOUNT_T_METALFATIGUE_PATCHOULI = 8;
constexpr int _SPLITONE_INTOEIGHT_BULLETCOUNT_T_METALFATIGUE_PATCHOULI = 64;
// �p�`�����[�i�T�C�����g�E�Z���i�j
constexpr int _CIRCLECONTIGUOUS_BULLETCOUNT_T_SILENTSERENA_PATCHOULI = 320;
constexpr int _SLOWLYCOMING_BULLETCOUNT_T_SILENTSERENA_PATCHOULI = 50;
// �`���m�i�m�[�}���j
constexpr int _STRAIGHTAPPROACH_BULLETCOUNT_T_NORMAL_CIRNO = 99;
constexpr int _EVERYDIRECTION_BULLETCOUNT_T_Normal_CIRNO = 48;



// ����̒e���p�^�[���𐶐�

class BulletHellFactory
{
public:

	BulletHellFactory();

	void InitBulletHellInfo();

	std::vector<Shared<EnemyBullet>> CreateBulletHell(const BulletHell::TYPE type);

private:

	// �p�`�����[�E�m�[���b�W------------------------------------------------------------------------------------------------------------
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
	std::vector<Shared<EnemyBullet>> CreateBulletHell_Normal_Patchouli();

	//// <summary>
	//  �� (�p�`�����[��p)
	// �~�`�A�����˂ƁA�����_���ɂ������߂Â��Ă���e��g�ݍ��킹���e��
	//// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_SilentSerena_Patchouli();

	//// <summary>
	//  �� (�p�`�����[��p)
	// �~���8way�e���W�J����A�r���ł��ꂼ�ꂪ8way�e�ɑ�����B
	//// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_MetalFatigue_Patchouli();

	//// <summary>
	/// ���@CreateBulletHell_MetalFatigue_Patchouli�֐��Ŏg�p����e���������W�b�N�̊֐���
	/// </summary>
	/// <param name="split_one_into_eight_WAVE1"></param>
	/// <param name="split_one_into_eight_bullet"></param>
	//// <param name="enemyBullet"></param>
	void InitSplitOneIntoEightBullet(int split_one_into_eight_WAVE1, Shared<EnemyBullet>& split_one_into_eight_bullet, std::vector<Shared<EnemyBullet>>& enemyBullet, const std::string& wave);

	// �`���m-------------------------------------------------------------------------------------------------------------------------
	//// <summary>
    //  �� (�`���m��p)
    // 1.�V���b�g�K���i3 + N)�s (N��0�`5�܂�)�A�U��̒e���v���C���[�֔���
    // 2.�Q����
    // 3.�R����
    // 4.�S�����΂�T���V���b�g
	// 5.�Q���ځi���̂Q���ڂ͂����ɏc���Ɏ������A�v���C���[�ւƕ������j
	// 6.�R����
	// 7.1�ɖ߂�
    //// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_Normal_Cirno();


	//// <summary>
    //  �� (�`���m��p)
    // 1.
    // 2.
    // 3.
    // 4.
    //// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_IcicleFall_Cirno();


	//// <summary>
	//  �� (�`���m��p)
	// 1.�S�����΂�T���V���b�g������
	// 2.�t���[�Y�A�e���~�߂Ĕ�������
	// 3.���@�ˑ����ꂽ�W�����V���b�g��A���ł���
	// 4.�~�߂Ă����e��S�����œ������n�߂�
	//// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_PerfectFreeze();

	//// <summary>
	//�@�� (�z�K�q��p)
	//�@1.��Ɍ�������8way�e������
	//�@2.���X�ɉ������ɉ������Ă���
	//// </summary>
	std::vector<Shared<EnemyBullet>> CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();


private:

	Shared<CsvLoader> _csvLoader = nullptr;

	Shared<BulletHell> _bulletHell = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};

	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;

	// ��Ɍ��_
	tnl::Vector3 _firstBossSpawnPosition{ 0,0,0 };
};