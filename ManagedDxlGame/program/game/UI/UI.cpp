#include "UI.h"

UI::UI() {

	player_hp_ = player_->get_hp_();
	score_ = ScoreManager::GetInstance_()->get_nowScore_();

	//hp_gpc_hdl = player_->hp_

}

void UI::update(float delta_time) {



}


void UI::draw() {

	//// hp‚ð‰æ–Ê‚É•\Ž¦
	//for (int h = 0; h < player_hp_; ++h) {
	//	DrawRotaGraph(hp_gpc_pos_.x + h * 50, hp_gpc_pos_.y, 2.0f, 0, hp_gpc_hdl_, true);
	//}

}
