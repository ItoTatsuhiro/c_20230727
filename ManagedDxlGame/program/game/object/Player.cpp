#include "Player.h"





Player::Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_) {

	play_Area_Size_Max = set_play_Area_Size_Max(PLAY_AREA_SIZE_MAX_);
	play_Area_Size_Min = set_play_Area_Size_Min(PLAY_AREA_SIZE_MIN_);


	// プレイヤーの画像アニメーションの読み込み
	player_anim_hdl_ = AnimManager::GetInstance_()->loadDivGraph(ANIM_CSV_OBJ::PLAYER);

	// プレイヤーの情報をcsvから読み込み
	playerData_ = tnl::LoadCsv(GameManager::GetInstance_()->csvAddress[static_cast<int>(GameManager::CSV_NAME::PLAYER_DATA)][0]);


	//const int Player::get_WIDTH() = AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::get_WIDTH())].getInt();
	//const int Player::HEIGHT = AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::HEIGHT)].getInt();

	// 初期位置の初期化
	startPos_ = {
		playerData_[static_cast<float>(PLAYER_CSV::START_POS)][1].getFloat(),
		playerData_[static_cast<float>(PLAYER_CSV::START_POS)][1].getFloat(),
		0 };
	// 移動速度の初期化
	moveSpeed_ = playerData_[static_cast<float>(PLAYER_CSV::MOVE_SPEED)][1].getFloat();
	// ジャンプ力の初期化
	jumpPower_ = playerData_[static_cast<float>(PLAYER_CSV::JUMP)][1].getFloat();
	// 重力の初期化
	gravity_ = playerData_[static_cast<float>(PLAYER_CSV::GRAVITY)][1].getFloat();
	// 体力の初期化
	hpMax_ = playerData_[static_cast<float>(PLAYER_CSV::HP)][1].getFloat();
	hp_ = hpMax_;
	// 体力の画像の読み込み
	hp_gpc_hdl_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::HEART);

	pos_ = startPos_;		// プレイヤーを初期位置に移動

	jumpSound_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::JUMP);
	ChangeVolumeSoundMem(200, jumpSound_hdl_);

	damageSound_hdl_ = SoundManager::GetInstance_()->loadSoundMem_(SOUND_KINDS::DAMAGE);
	ChangeVolumeSoundMem(255, damageSound_hdl_);

}

Player::~Player() {



}

void Player::update(float delta_time) {

	move(delta_time);

	if (hitIntervalCount_ < hitInterval_) {
		hitIntervalCount_ += delta_time;
		if (hitIntervalCount_ > hitInterval_) {
			hitIntervalCount_ = hitInterval_;
		}
	}
	

}

void Player::draw(float delta_time) {

	// hpを画面に表示
	for (int h = 0; h < hp_; ++h) {
		DrawRotaGraph(hp_gpc_pos_.x + h * 50, hp_gpc_pos_.y, 2.0f, 0, hp_gpc_hdl_, true);
	}

	anim_time_count_ += delta_time;		// アニメーション画像の表示時間をカウント


	if (hp_ > 0) {

		if (anim_time_count_ > anim_time_change_) {

			// 表示するアニメーション画像を次に送る
			++anim_ctrl_flame_;
			// 再生するアニメーションの画像をループするようにする
			anim_ctrl_flame_ %= AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::TOTAL_FLAME)].getInt();
			// 表示時間を0に戻す
			anim_time_count_ = 0;

		}

		// ダメージを受けた際に点滅させる処理
		if (hitIntervalCount_ < hitInterval_) {
			hitFlashTimeCount_ += delta_time;
			if (hitFlashTimeCount_ >= hitFlashTime_) {
				if (playerView_)		playerView_ = false;
				else if (!playerView_)	playerView_ = true;
				hitFlashTimeCount_ = 0;
			}
		}
	}

	// 点滅時間が過ぎたのちにプレイヤーが消えている場合表示
	if (hitIntervalCount_ >= hitInterval_ && playerView_ == false) {
		playerView_ = true;
		hitFlashTimeCount_ = 0;
	}


	if (playerView_) {

		// プレイヤーを表示
		DrawRotaGraph(pos_.x, pos_.y, anim_size_, 0, player_anim_hdl_[anim_ctrl_flame_], true);

	}

	//DrawStringEx(500, 500, -1, "play_Area_Size_Max.x = %f, y = %f", play_Area_Size_Max.x, play_Area_Size_Max.y);
	//DrawStringEx(500, 550, -1, "play_Area_Size_Min = %f, y = %f", play_Area_Size_Min.x, play_Area_Size_Min.y);

}

tnl::Vector3 Player::set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_) {
	play_Area_Size_Max = PLAY_AREA_SIZE_MAX_;
	return play_Area_Size_Max;
}

tnl::Vector3 Player::set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_) {
	play_Area_Size_Min = PLAY_AREA_SIZE_MIN_;
	return play_Area_Size_Min;
}

tnl::Vector3& Player::getPlayerPos() {

	return pos_;
}

void Player::setPlayerPos(const tnl::Vector3& newPlayerPos) {

	pos_ = newPlayerPos;
}

//int& Player::get_playerRadius() {
//	return player_r;
//}

const float& Player::get_move_speed_() {
	return moveSpeed_;
}

const int& Player::get_WIDTH() {
	return AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::WIDTH)].getInt() * anim_size_;
}

const int& Player::get_HEIGHT() {
	return AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::HEIGHT)].getInt() * anim_size_;
}




// プレイヤーキャラクターの動きについて
void Player::move(float delta_time) {

	posPrev_ = pos_;

	moveValue_.y += gravity_ * timeFall_;
	timeFall_ += delta_time;				// 落下時間の加算


	if (hp_ > 0) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) && pos_.x != -moveSpeed_) {			// Aキーを押しているとき
			moveValue_.x = -moveSpeed_;											// 左に座標を移動
			if (pos_.x <= play_Area_Size_Min.x + get_WIDTH()) {
				pos_.x = play_Area_Size_Min.x + get_WIDTH();						// 画面の範囲からはみ出たとき画面内に戻す
			}
		}

		if ((tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) && pos_.x != moveSpeed_) {		// Dキーを押しているとき
			moveValue_.x = moveSpeed_;												// 右に座標を移動
			if (pos_.x >= play_Area_Size_Max.x - get_WIDTH()) {
				pos_.x = play_Area_Size_Max.x - get_WIDTH();						// 画面の範囲からはみ出たとき画面内に戻す
			}
		}

		// 方向キーが押されていない状態では横の移動量を0にする
		if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_A) && !(tnl::Input::IsKeyDown(eKeys::KB_D)) ||
			tnl::Input::IsKeyReleaseTrigger(eKeys::KB_D) && !(tnl::Input::IsKeyDown(eKeys::KB_A))) {
			moveValue_.x = 0;
		}

		if (jumpCount_ < jumpMax_) {								// ジャンプ可能な時のみ

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX)) {
				PlaySoundMem(jumpSound_hdl_, DX_PLAYTYPE_BACK);
				moveValue_.y = -jumpPower_;							// ジャンプの処理
				timeFall_ = 0;
				++jumpCount_;		// ジャンプ回数のカウントを増やす
			}
		}

	}
	else if (hp_ <= 0) {
		moveValue_.x = 0;
	}



	pos_ += moveValue_;										// 移動量の加算

	if (pos_.y > play_Area_Size_Max.y - get_HEIGHT() / 2) {
		pos_.y = play_Area_Size_Max.y - get_HEIGHT() / 2;
		timeFall_ = 0;
		moveValue_.y = 0;
	}


	//DrawStringEx(100, 300, -1, "timeFall_ = %f", timeFall_);	// 落下時間の表示

}

// hpの値を取得する関数
const float& Player::get_hp_() {
	return hp_;
}

// hpの値を変更する関数
void Player::set_hp_(const float damage) {

	if (hitIntervalCount_ >= hitInterval_ || damage < 0) {

		if (damage > 0) {
			set_hitIntervalCount_(0);		// ダメージを受けてからの時間を0にリセットする
		}

		hp_ -= damage;
		PlaySoundMem(damageSound_hdl_, DX_PLAYTYPE_BACK);

	}

	if (hp_ > hpMax_)	hp_ = hpMax_;	// 体力が最大値より大きくなった時最大値に戻す
	else if (hp_ < 0)	hp_ = 0;		// 体力が0より小さくなったとき0にする
}

void Player::set_hitIntervalCount_(float time) {
	hitIntervalCount_ = time;
}


void Player::set_jumpCount_(int count) {
	jumpCount_ = count;
}
