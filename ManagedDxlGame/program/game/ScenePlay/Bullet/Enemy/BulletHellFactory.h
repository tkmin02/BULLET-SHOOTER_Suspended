#pragma once

class BulletHell;

// ����̒e���p�^�[���𐶐�

class BulletHellFactory
{
public:

	BulletHellFactory();

	void InitBulletHellInfo();

	Shared<BulletHell> CreateBulletHell(const BulletHell::TYPE type, const Shared<dxe::Mesh>& bossMesh_ref);


	//Shared<BulletHell> ReuseBulletHell_SilentSerena(int id);


	//Shared<BulletHell> GetBulletHell(int id);

private:

	//// <summary>
	//  �� (�p�`�����[��p)
	// �~�`�A�����˂ƁA�����_���ɂ�����藎���Ă���e��g�ݍ��킹���e��
	//// </summary>
	Shared<BulletHell> CreateBulletHell_SilentSerena(const Shared<dxe::Mesh>& bossMesh_ref);

	//// <summary>
	//  �� (�`���m��p)
	// 1.�S�����΂�T���V���b�g������
	// 2.�t���[�Y�A�e���~�߂Ĕ�������
	// 3.���@�ˑ����ꂽ�W�����V���b�g��A���ł���
	// 4.�~�߂Ă����e��S�����œ������n�߂�
	//// </summary>
	Shared<BulletHell> CreateBulletHell_PerfectFreeze(const Shared<dxe::Mesh>& bossMesh_ref);

	//// <summary>
	//�@�� (�z�K�q��p)
	//�@1.��Ɍ�������8way�e������
	//�@2.���X�ɉ������ɉ������Ă���
	//// </summary>
	Shared<BulletHell> CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm(const Shared<dxe::Mesh>& bossMesh_ref);

private:

	Shared<CsvLoader> _csvLoader = nullptr;

private:

	BulletHellType_Info _sBltHell_patchouli_info{};
	BulletHellType_Info _sBltHell_cirno_info{};
	BulletHellType_Info _sBltHell_suwako_info{};



	std::unordered_map<int, BulletHellType_Info> _bulletHellData_map;

	//std::map<int, Shared<BulletHell>> bulletHellMap;
};

