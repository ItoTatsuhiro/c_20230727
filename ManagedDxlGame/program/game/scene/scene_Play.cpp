#include <algorithm>

#include "scene_Play.h"

ScenePlay::ScenePlay() {

	player_ = new Player(PLAY_AREA_SIZE_MAX, PLAY_AREA_SIZE_MIN);			// プレイヤーの生成
	stage_ = new Stage();
	background_ = new BackGround(GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::BACK_GRASS));

	ScoreManager::GetInstance_()->scoreReset();

	playBGM_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::PLAY);
	ChangeVolumeSoundMem(200, playBGM_hdl_);
	PlaySoundMem(playBGM_hdl_, DX_PLAYTYPE_LOOP);


}


ScenePlay::~ScenePlay() {

	delete player_;
	player_ = nullptr;
	delete stage_;
	stage_ = nullptr;
	delete background_;
	background_ = nullptr;

	StopSoundMem(playBGM_hdl_);
}


void ScenePlay::update(float delta_time) {

	if (player_ != nullptr) {
		player_->update(delta_time);
	}

	// プレイヤーのhpがある時スコアを加算
	if (player_->get_hp_() > 0) {
		ScoreManager::GetInstance_()->scoreCount_(delta_time);

		if (stage_ != nullptr) {
			stage_->update(delta_time);
		}

	}

	// 当たり判定の確認
	hitCheck();

	if (player_->get_hp_() <= 0) {
		sceneplayFin_();
	}

}


void ScenePlay::draw(float delta_time) {

	if (background_ != nullptr) background_->draw();
	if (stage_ != nullptr) stage_->draw();
	if (player_ != nullptr) player_->draw(delta_time);


	SetFontSize(50);
	DrawStringEx(900, 100, 0, "SCORE：%d", ScoreManager::GetInstance_()->get_nowScore_());

	if (player_->get_hp_() <= 0) {
		SetFontSize(100);
		DrawStringEx(350, 250, -1, "F I N I S H !");

		SetFontSize(45);
		DrawStringEx(450, 600, -1, "enterキーで結果発表へ");
	}

}

tnl::Vector3 ScenePlay::get_PLAY_AREA_SIZE_MAX() {
	return PLAY_AREA_SIZE_MAX;
}

tnl::Vector3 ScenePlay::get_PLAY_AREA_SIZE_MIN() {
	return PLAY_AREA_SIZE_MIN;
}


bool ScenePlay::seqIdle(const float delta_time) {
	return true;
}

void ScenePlay::hitCheck() {

	auto it = stage_->get_stageMap_Chunk_Obj_().begin();

	//DrawStringEx(500, 100, -1, "PlayerPos = %f, %f", player_->getPlayerPos().x, player_->getPlayerPos().y);


	while (it != stage_->get_stageMap_Chunk_Obj_().end()) {

		for (int y = 0; y < stage_->get_stageCutNumber_().y; ++y) {
			for (int x = 0; x < stage_->get_stageCutNumber_().x; ++x) {

				if ((*it)[y][x] == nullptr) continue;

				if ((*it)[y][x]->get_has_damage_() == true) {
					if (tnl::IsIntersectRect(
						player_->getPlayerPos(),		// プレイヤーの座標
						player_->get_moveValue_().x + player_->get_WIDTH(),			// プレイヤーの横幅(移動量+幅)
						player_->get_moveValue_().y + player_->get_HEIGHT(),		// プレイヤーの縦幅(移動量+縦幅)
						(*it)[y][x]->getPos_(),										// マップチップの座標
						stage_->get_mapchipSize_(),									// マップチップの横幅
						stage_->get_mapchipSize_())) {								// マップチップの縦幅

						player_->set_hp_((*it)[y][x]->get_damageVal_());			// プレイヤーの体力を調整する

					}
				}

				if ((*it)[y][x]->getCollision() == true) {


					// マップチップとプレイヤーの衝突判定
					if (tnl::IsIntersectRect(
						player_->getPlayerPos(),		// プレイヤーの座標
						player_->get_moveValue_().x + player_->get_WIDTH(),			// プレイヤーの横幅(移動量+幅)
						player_->get_moveValue_().y + player_->get_HEIGHT(),		// プレイヤーの縦幅(移動量+縦幅)
						(*it)[y][x]->getPos_(),										// マップチップの座標
						stage_->get_mapchipSize_(),									// マップチップの横幅
						stage_->get_mapchipSize_())) {								// マップチップの縦幅


						float playerRight = player_->getPlayerPos().x + (player_->get_WIDTH() / 2);
						float playerBottom = player_->getPlayerPos().y + (player_->get_HEIGHT() / 2);
						float blockRight = (*it)[y][x]->getPos_().x + (stage_->get_mapchipSize_() / 2);
						float blockBottom = (*it)[y][x]->getPos_().y + (stage_->get_mapchipSize_() / 2);


						float overlap_x = 0.0f;					// 重なっている量：x
						float overlap_y = 0.0f;					// 重なっている量：y

						// overlap_xの値を設定(プレイヤーとブロックの左右を確認)
						if (playerRight - ((*it)[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2) > blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2)) {

							overlap_x = blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2);
						}
						else {
							overlap_x = playerRight - ((*it)[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2);
						}

						// overlap_yの値を設定(プレイヤーとブロックの上下を確認)
						if (playerBottom - ((*it)[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2) > blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2)) {

							overlap_y = blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2);
						}
						else {

							overlap_y = playerBottom - ((*it)[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2);
						}

						if (overlap_x < overlap_y) {
							// X軸方向の衝突
							if (player_->getPlayerPos().x < (*it)[y][x]->getPos_().x) {
								// プレイヤーが左から衝突
								player_->setPlayerPos(player_->getPlayerPos() - tnl::Vector3(overlap_x, 0.0f, 0.0f));
							}
							else {
								// プレイヤーが右から衝突
								player_->setPlayerPos(player_->getPlayerPos() + tnl::Vector3(overlap_x, 0.0f, 0.0f));
							}
							// X軸方向の速度を0に設定
							player_->set_moveValue_(tnl::Vector3(0, player_->get_moveValue_().y, 0));

						}
						else {
							// Y軸方向の衝突
							if (player_->getPlayerPos().y < (*it)[y][x]->getPos_().y) {

								// プレイヤーが上から衝突
								player_->setPlayerPos(player_->getPlayerPos() - tnl::Vector3(0.0f, overlap_y, 0.0f));

								// 落下時間をリセット
								player_->reset_timeFall_();

							}
							else {

								// プレイヤーが下から衝突
								player_->setPlayerPos(player_->getPlayerPos() + tnl::Vector3(0.0f, overlap_y, 0.0f));
							}

							// Y軸方向の速度を0に設定
							player_->set_moveValue_(tnl::Vector3(player_->get_moveValue_().x, 0, 0));

						}

						// ここでプレイヤーのジャンプ回数を回復させる 
						//DrawStringEx(500, 700, -1, "hit");


						// 接地した際にジャンプ回数を回復させる
						if (player_->get_jumpCount_() == player_->get_jumpMax_()) {
							player_->set_jumpCount_(0);
						}
					}


				}
				
			}
		}
		++it;
	}
}


// プレイシーンの終了時の処理
void ScenePlay::sceneplayFin_() {


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX)) {
		auto mgr = GameManager::GetInstance_();
		mgr->changeScene(new SceneResult());
	}

}