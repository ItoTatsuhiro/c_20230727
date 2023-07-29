#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "common/GameManager.h"
#include "scene/scene_Title.h"


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));

	// �Q�[���}�l�[�W���[�̃C���X�^���X��
	GameManager* gmr = GameManager::GetInstance(new SceneTitle());

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	GameManager::GetInstance()->update(delta_time);


}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
