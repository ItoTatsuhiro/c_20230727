#include "Player.h"

Player::Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_) {

	play_Area_Size_Max = set_play_Area_Size_Max(PLAY_AREA_SIZE_MAX_);
	play_Area_Size_Min = set_play_Area_Size_Min(PLAY_AREA_SIZE_MIN_);

	pos_ = PLAYER_START_POS;

}

Player::~Player() {



}

void Player::update(float delta_time) {

	move(delta_time);

}

void Player::draw() {

	DrawCircle(pos_.x, pos_.y, 10, -1, 0);

	DrawStringEx(500, 500, -1, "play_Area_Size_Max.x = %f, y = %f", play_Area_Size_Max.x, play_Area_Size_Max.y);
	DrawStringEx(500, 550, -1, "play_Area_Size_Min = %f, y = %f", play_Area_Size_Min.x, play_Area_Size_Min.y);

}

tnl::Vector3 Player::set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_) {
	play_Area_Size_Max = PLAY_AREA_SIZE_MAX_;
	return play_Area_Size_Max;
}

tnl::Vector3 Player::set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_) {
	play_Area_Size_Min = PLAY_AREA_SIZE_MIN_;
	return play_Area_Size_Min;
}

// プレイヤーキャラクターの動きについて
void Player::move(float delta_time) {

	move_y_value += gravity * time_fall;

	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {	// Aキーを押しているとき
		pos_.x -= move_speed;					// 左に座標を移動
		if (pos_.x <= play_Area_Size_Min.x + player_r) {
			pos_.x = play_Area_Size_Min.x + player_r;		// 画面の範囲からはみ出たとき画面内に戻す
		}
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {	// Dキーを押しているとき
		pos_.x += move_speed;						// 右に座標を移動
		if (pos_.x >= play_Area_Size_Max.x - player_r) {
			pos_.x = play_Area_Size_Max.x - player_r;		// 画面の範囲からはみ出たとき画面内に戻す
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		move_y_value = -jump_power;				// ジャンプの処理
		time_fall = 0;
	}

	pos_.y += move_y_value;						// 落下の処理

	if (pos_.y >= 700) {
		pos_.y = 700;
	}

	time_fall += delta_time;

	DrawStringEx(100, 300, -1, "time_fall = %f", time_fall);

}

