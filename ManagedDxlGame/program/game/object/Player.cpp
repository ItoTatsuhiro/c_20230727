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

	DrawBoxEx(pos_, WIDTH, HEIGHT, true);
	//DrawCircle((int)pos_.x, (int)pos_.y, player_r, -1, 0);

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
	return move_speed;
}

const float& Player::get_WIDTH() {
	return WIDTH;
}

const float& Player::get_HEIGHT() {
	return HEIGHT;
}

//const tnl::Vector3& Player::get_moveValue_() {
//	return moveValue_;
//}

// �v���C���[�L�����N�^�[�̓����ɂ���
void Player::move(float delta_time) {

	posPrev_ = pos_;

	moveValue_.y += gravity * timeFall_;
	timeFall_ += delta_time;				// �������Ԃ̉��Z


	if (tnl::Input::IsKeyDown(eKeys::KB_A) && pos_.x != -move_speed) {		// A�L�[�������Ă���Ƃ�
		moveValue_.x = - move_speed;												// ���ɍ��W���ړ�
		if (pos_.x <= play_Area_Size_Min.x + WIDTH) {
			pos_.x = play_Area_Size_Min.x + WIDTH;						// ��ʂ͈̔͂���͂ݏo���Ƃ���ʓ��ɖ߂�
		}
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D) && pos_.x != move_speed) {		// D�L�[�������Ă���Ƃ�
		moveValue_.x = move_speed;												// �E�ɍ��W���ړ�
		if (pos_.x >= play_Area_Size_Max.x - WIDTH) {
			pos_.x = play_Area_Size_Max.x - WIDTH;						// ��ʂ͈̔͂���͂ݏo���Ƃ���ʓ��ɖ߂�
		}
	}

	// 
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_A) && !(tnl::Input::IsKeyDown(eKeys::KB_D)) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_D) && !(tnl::Input::IsKeyDown(eKeys::KB_A))) {
		moveValue_.x = 0;
	}

	pos_ += moveValue_;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
 		moveValue_.y = -jump_power;							// �W�����v�̏���
		timeFall_ = 0;
	}

	pos_ += moveValue_;										// �ړ��ʂ̉��Z

	if (pos_.y > play_Area_Size_Max.y - HEIGHT / 2) {
		pos_.y = play_Area_Size_Max.y - HEIGHT / 2;
		timeFall_ = 0;
		moveValue_.y = 0;
	}


	DrawStringEx(100, 300, -1, "timeFall_ = %f", timeFall_);

}

