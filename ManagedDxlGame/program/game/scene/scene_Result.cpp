#include "scene_Result.h"

SceneResult::SceneResult() {

	nowScore_ = ScoreManager::GetInstance_()->get_nowScore_();
	highScore_ = ScoreManager::GetInstance_()->get_highScore_();

	textColor_highScore_ = 0;

	background_ = new BackGround(GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::BACK_GRASS));


	resultBGM_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::RESULT);
	ChangeVolumeSoundMem(200, resultBGM_hdl_);

	resultDis_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::RESULT_DIS);
	ChangeVolumeSoundMem(200, resultDis_hdl_);
	
}

//SceneResult::~SceneResult() {
//
//}


void SceneResult::update(float delta_time) {
	sequence_.update(delta_time);


	if (textDisplayPhase_ * textDisplayTimeInterval_ <= textDisplayTimeCount_) {

		++textDisplayPhase_;

	}

	if (textDisplayPhase_ >= static_cast<int>(RESULT_DIS_PHASE::COMMAND)) {

		ScoreManager::GetInstance_()->highScoreUpdate();

		// スコアがハイスコアより高いとき
		if (nowScore_ > highScore_) {
			highScore_ = nowScore_;				// ハイスコアの値を更新する
			textColor_highScore_ = 0xffff00;	// 表示する色を変更
			PlaySoundMem(resultBGM_hdl_, DX_PLAYTYPE_BACK);
		
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
			if (selectCommand_ == RESULT_COMMAND::RESTART) selectCommand_ = RESULT_COMMAND::TITLE;
			else if (selectCommand_ == RESULT_COMMAND::TITLE) selectCommand_ = RESULT_COMMAND::RESTART;
		}
		 else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
			if (selectCommand_ == RESULT_COMMAND::RESTART) selectCommand_ = RESULT_COMMAND::TITLE;
			else if (selectCommand_ == RESULT_COMMAND::TITLE) selectCommand_ = RESULT_COMMAND::RESTART;
		}

		if (selectCommand_ == RESULT_COMMAND::RESTART && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			auto mgr = GameManager::GetInstance_();
			mgr->changeScene(new ScenePlay());

		}


		if (selectCommand_ == RESULT_COMMAND::TITLE && (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX))) {
			auto mgr = GameManager::GetInstance_();
			mgr->changeScene(new SceneTitle());

		}

	}
	textDisplayTimeCount_ += delta_time;

}

void SceneResult::draw(float delta_time) {

	if (background_ != nullptr) background_->draw();

	
	//PlaySoundMem(resultDis_hdl_, DX_PLAYTYPE_BACK);


	if (textDisplayPhase_ >= static_cast<int>(RESULT_DIS_PHASE::TITLE)) {
		SetFontSize(50);
		DrawStringEx(resultTextPos_.x, resultTextPos_.y, 0, "R E S U L T");
	}
	if (textDisplayPhase_ >= static_cast<int>(RESULT_DIS_PHASE::NOW_SCORE)) {
		SetFontSize(40);
		DrawStringEx(nowScorePos_.x, nowScorePos_.y, 0, "SCORE = %d", nowScore_);
	}

	if (textColor_highScore_ != -1) {
		SetFontSize(30);
		DrawStringEx(highScorePos_.x, highScorePos_.y - 30, textColor_highScore_, "ハイスコア更新！");
	}

	if (textDisplayPhase_ >= static_cast<int>(RESULT_DIS_PHASE::HIGH_SCORE)) {
		SetFontSize(40);
		DrawStringEx(highScorePos_.x, highScorePos_.y, textColor_highScore_, "HIGHSCORE = %d", highScore_);
	}
	if (textDisplayPhase_ >= static_cast<int>(RESULT_DIS_PHASE::COMMAND)) {

		if (selectCommand_ == RESULT_COMMAND::RESTART) {
			SetFontSize(30);
			DrawStringEx(commandRestartPos_.x, commandRestartPos_.y, 0xffff0000, "RESTART");		// 赤で表示

			SetFontSize(20);
			DrawStringEx(commandReturnTitlePos_.x, commandReturnTitlePos_.y, 0, "RETURN TITLE");	// 黒で表示
		}
		else if (selectCommand_ == RESULT_COMMAND::TITLE) {
			SetFontSize(20);
			DrawStringEx(commandRestartPos_.x, commandRestartPos_.y, 0, "RESTART");		// 黒で表示
			SetFontSize(30);
			DrawStringEx(commandReturnTitlePos_.x, commandReturnTitlePos_.y, 0xffff0000, "RETURN TITLE");	// 赤で表示
		}
	}






	//if (TitleSelect_now == TITLE_START) {
	//	SetFontSize(30);
	//	DrawStringEx(Start_pos.x, Start_pos.y, 0xffff0000, "Start");		// 赤で表示

	//	SetFontSize(20);
	//	DrawStringEx(Start_pos.x, Start_pos.y + MENU_SPACE, -1, "Exit");	// 黒で表示
	//}
	//else if (TitleSelect_now == TITLE_EXIT) {
	//	SetFontSize(20);
	//	DrawStringEx(Start_pos.x, Start_pos.y, -1, "Start");		// 黒で表示
	//	SetFontSize(30);
	//	DrawStringEx(Start_pos.x, Start_pos.y + MENU_SPACE, 0xffff0000, "Exit");	// 赤で表示
	//}



}


bool SceneResult::seqIdle(const float delta_time) {
	return true;
}