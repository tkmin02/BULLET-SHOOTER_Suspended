#include "DxLibEngine.h"
#include "gm_main.h"
#include "Manager/Scene/SceneManager.h"
#include "SceneTitle/SceneTitle.h"
#include "SceneSelectDifficulty/SceneSelectDifficulty.h"
#include "ScenePlay/ScenePlay.h"
#include "ScenePlay/Character/Enemy/EnemyBase.h"
#include "ScenePlay/Character/Enemy/EnemyZakoBase.h"
#include "ScenePlay/Character/Player/Player.h"


void LockCursorToWindow() {

    HWND hwnd = GetMainWindowHandle(); // DX���C�u�����ŃE�B���h�E�n���h�����擾
    RECT rect;
    GetClientRect(hwnd, &rect); // �N���C�A���g�̈�̃T�C�Y���擾

    POINT ul;
    ul.x = rect.left;
    ul.y = rect.top;

    POINT lr;
    lr.x = rect.right;
    lr.y = rect.bottom;

    MapWindowPoints(hwnd, nullptr, &ul, 1); // �N���C�A���g�̈�̍���̃X�N���[�����W�ւ̕ϊ�
    MapWindowPoints(hwnd, nullptr, &lr, 1); // �N���C�A���g�̈�̉E���̃X�N���[�����W�ւ̕ϊ�

    RECT clipRect;
    clipRect.left = ul.x;
    clipRect.top = ul.y;
    clipRect.right = lr.x;
    clipRect.bottom = lr.y;

    ClipCursor(&clipRect); // �J�[�\�������̗̈�ɐ���
}


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {

	srand(time(0));
	//// �f�B���N�V���i�����C�g
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	 //�w�i�F
	SetBackgroundColor(64, 64, 64);
	//SetMouseDispFlag(false);
    //LockCursorToWindow();

	SceneManager::GetInstance(new SceneTitle());
}


bool isFullScreen = true;
//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	SceneManager::GetInstance()->Update(delta_time);

	//if (tnl::Input::IsKeyDown(eKeys::KB_ESCAPE)) isFullScreen = !isFullScreen;

	//if (isFullScreen) ChangeWindowMode(false);
	//else              ChangeWindowMode(true);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) exit(1);

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}


// ���@[ �d�v ]�@std::shared_ptr �Ŋm�ۂ��� dxe::Particle �͕K�� gameEnd() ��
// �@�@�^�C�~���O�܂łɎQ�ƃJ�E���^�� 0 �ɂȂ�悤���Z�b�g���Ă������� ( gameEnd �֐����Q�� )
//
// ���@[ �d�v ]�@���̋@�\�� DxLib �̋@�\�ł͂���܂���
// �@�@dxe::Particle �� dxe::InstMeshPool �Ȃ� DirectX �𒼐ڐ��䂷��N���X�� render �֐���
//�@�@ dxe::DirectXRenderBegin() dxe::DirectXRenderEnd() �ň͂������ŃR�[�����Ă�������  
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	EnemyZakoBase::_explode_particle.reset();
	ScenePlay::_weather_particle.reset();
	Player::_bomb_particle.reset();
}