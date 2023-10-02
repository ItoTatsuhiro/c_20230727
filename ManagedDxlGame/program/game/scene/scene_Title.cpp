#include "scene_Title.h"


SceneTitle::SceneTitle() {

	background_ = new BackGround( GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::BACK_GRASS) );
	titleBGM_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::TITLE);
	ChangeVolumeSoundMem(200, titleBGM_hdl_);
	PlaySoundMem(titleBGM_hdl_, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle() {
	delete background_;
	background_ = nullptr;
	StopSoundMem(titleBGM_hdl_);

}

void SceneTitle::update(float delta_time) {
	sequence_.update(delta_time);


	//�㉺�L�[�őI�𒆂̑I������؂�ւ���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_D) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)) {
		if (Select_now == TitleSelect::TITLE_START) {
			Select_now = TitleSelect::TITLE_EXIT;
		}
		else if (Select_now == TitleSelect::TITLE_EXIT) {
			Select_now = TitleSelect::TITLE_START;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_A) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)) {
		if (Select_now == TitleSelect::TITLE_START) {
			Select_now = TitleSelect::TITLE_EXIT;
		}
		else if (Select_now == TitleSelect::TITLE_EXIT) {
			Select_now = TitleSelect::TITLE_START;
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX)) {
		if (Select_now == TitleSelect::TITLE_START) {
			auto mgr = GameManager::GetInstance_();
			mgr->changeScene(new ScenePlay());
		}
		else if (Select_now == TitleSelect::TITLE_EXIT) {
			DxLib_End();
		}
	}
	

}

void SceneTitle::draw(float delta_time) {

	
	if (background_ != nullptr) background_->draw();		// �w�i�̕`��

	SetFontSize(100);

	DrawStringEx(Title_pos.x, Title_pos.y, 0, "�V�X�^�[��@�ꔯ!");

	//SetFontSize(20);


	if (Select_now == TitleSelect::TITLE_START) {
		SetFontSize(50);
		DrawStringEx(Start_pos.x, Start_pos.y, 0xffff0000, "Start");		// �Ԃŕ\��

		SetFontSize(40);
		DrawStringEx(Start_pos.x + MENU_SPACE, Start_pos.y, 0, "Exit");	// ���ŕ\��
	}
	else if (Select_now == TitleSelect::TITLE_EXIT) {
		SetFontSize(40);
		DrawStringEx(Start_pos.x, Start_pos.y, 0, "Start");		// ���ŕ\��
		SetFontSize(50);
		DrawStringEx(Start_pos.x + MENU_SPACE, Start_pos.y, 0xffff0000, "Exit");	// �Ԃŕ\��
	}
}

bool SceneTitle::seqIdle(float delta_time) {
	return true;
}