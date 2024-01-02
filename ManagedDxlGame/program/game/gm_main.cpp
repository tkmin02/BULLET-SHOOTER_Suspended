#include <string>
#include "DxLibEngine.h"
#include "gm_main.h"
#include "Manager/Scene/SceneManager.h"
#include "ScenePlay/ScenePlay.h"


/*   TASK

�v���C���[�L�����N�^�[�F�v���C���[�����삷��L�����N�^�[�ł��B�ړ��A�U���A�h��Ȃǂ̊�{�I�ȃA�N�V���������ׂ��ł��B

�G�L�����N�^�[�F�v���C���[���키�ΏۂƂȂ�L�����N�^�[�ł��B�قȂ��ނ̍U���p�^�[����s���p�^�[�������ׂ��ł��B

�e���i�e�j�F�G�L�����N�^�[�����˂��A�v���C���[��������ׂ��v���W�F�N�g�ł��B

�X�e�[�W�F�Q�[�����i�s�������w�i�ł��B�R�c�̃Q�[���ł́A�X�e�[�W�f�U�C���̓Q�[���̌��ɑ傫�ȉe����^���܂��B

�X�R�A�V�X�e���F�v���C���[�̃p�t�H�[�}���X��]�����邽�߂̃V�X�e���ł��B�G��|���A�e���������A����ȃA�N�V�������s���ȂǁA�l�X�ȗv�f�Ɋ�Â��ăX�R�A���v�Z���邱�Ƃ��ł��܂��B

UI�i���[�U�[�C���^�[�t�F�[�X�j�F�v���C���[�̃X�R�A�A���C�t�A�p���[�A�b�v�Ȃǂ̏���\�����邽�߂̃C���^�[�t�F�[�X�ł��B

�T�E���h�G�t�F�N�g�Ɖ��y�F�Q�[���̕��͋C�����߁A�v���C���[�̍s���Ƀt�B�[�h�o�b�N��񋟂��邽�߂̏d�v�ȗv�f�ł��B

�p���[�A�b�v�ƃA�C�e���F�v���C���[���Q�[�����ɏW�߂邱�Ƃ��ł��A�ꎞ�I�Ƀp���[�A�b�v������A���C�t���񕜂����肷��A�C�e���ł��B

*/



//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {

	srand(time(0));
	//// �f�B���N�V���i�����C�g
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	 //�w�i�F
	SetBackgroundColor(64, 64, 64);


	SceneManager::GetInstance(new ScenePlay());
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	SceneManager::GetInstance()->Update(delta_time);

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
