#include "Player.h"





Player::Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_) {

	play_Area_Size_Max = set_play_Area_Size_Max(PLAY_AREA_SIZE_MAX_);
	play_Area_Size_Min = set_play_Area_Size_Min(PLAY_AREA_SIZE_MIN_);


	// �v���C���[�̉摜�A�j���[�V�����̓ǂݍ���
	player_anim_hdl_ = AnimManager::GetInstance_()->loadDivGraph(ANIM_CSV_OBJ::PLAYER);

	// �v���C���[�̏���csv����ǂݍ���
	playerData_ = tnl::LoadCsv(GameManager::GetInstance_()->csvAddress[static_cast<int>(GameManager::CSV_NAME::PLAYER_DATA)][0]);


	//const int Player::get_WIDTH() = AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::get_WIDTH())].getInt();
	//const int Player::HEIGHT = AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::HEIGHT)].getInt();

	// �����ʒu�̏�����
	startPos_ = {
		playerData_[static_cast<float>(PLAYER_CSV::START_POS)][1].getFloat(),
		playerData_[static_cast<float>(PLAYER_CSV::START_POS)][1].getFloat(),
		0 };
	// �ړ����x�̏�����
	moveSpeed_ = playerData_[static_cast<float>(PLAYER_CSV::MOVE_SPEED)][1].getFloat();
	// �W�����v�͂̏�����
	jumpPower_ = playerData_[static_cast<float>(PLAYER_CSV::JUMP)][1].getFloat();
	// �d�͂̏�����
	gravity_ = playerData_[static_cast<float>(PLAYER_CSV::GRAVITY)][1].getFloat();
	// �̗͂̏�����
	hpMax_ = playerData_[static_cast<float>(PLAYER_CSV::HP)][1].getFloat();
	hp_ = hpMax_;
	// �̗͂̉摜�̓ǂݍ���
	hp_gpc_hdl_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::HEART);

	pos_ = startPos_;		// �v���C���[�������ʒu�Ɉړ�

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

	// hp����ʂɕ\��
	for (int h = 0; h < hp_; ++h) {
		DrawRotaGraph(hp_gpc_pos_.x + h * 50, hp_gpc_pos_.y, 2.0f, 0, hp_gpc_hdl_, true);
	}

	anim_time_count_ += delta_time;		// �A�j���[�V�����摜�̕\�����Ԃ��J�E���g


	if (hp_ > 0) {

		if (anim_time_count_ > anim_time_change_) {

			// �\������A�j���[�V�����摜�����ɑ���
			++anim_ctrl_flame_;
			// �Đ�����A�j���[�V�����̉摜�����[�v����悤�ɂ���
			anim_ctrl_flame_ %= AnimManager::GetInstance_()->anim_data_[static_cast<int>(ANIM_CSV_OBJ::PLAYER)][static_cast<int>(ANIM_CSV_ARG::TOTAL_FLAME)].getInt();
			// �\�����Ԃ�0�ɖ߂�
			anim_time_count_ = 0;

		}

		// �_���[�W���󂯂��ۂɓ_�ł����鏈��
		if (hitIntervalCount_ < hitInterval_) {
			hitFlashTimeCount_ += delta_time;
			if (hitFlashTimeCount_ >= hitFlashTime_) {
				if (playerView_)		playerView_ = false;
				else if (!playerView_)	playerView_ = true;
				hitFlashTimeCount_ = 0;
			}
		}
	}

	// �_�Ŏ��Ԃ��߂����̂��Ƀv���C���[�������Ă���ꍇ�\��
	if (hitIntervalCount_ >= hitInterval_ && playerView_ == false) {
		playerView_ = true;
		hitFlashTimeCount_ = 0;
	}


	if (playerView_) {

		// �v���C���[��\��
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




// �v���C���[�L�����N�^�[�̓����ɂ���
void Player::move(float delta_time) {

	posPrev_ = pos_;

	moveValue_.y += gravity_ * timeFall_;
	timeFall_ += delta_time;				// �������Ԃ̉��Z


	if (hp_ > 0) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) && pos_.x != -moveSpeed_) {			// A�L�[�������Ă���Ƃ�
			moveValue_.x = -moveSpeed_;											// ���ɍ��W���ړ�
			if (pos_.x <= play_Area_Size_Min.x + get_WIDTH()) {
				pos_.x = play_Area_Size_Min.x + get_WIDTH();						// ��ʂ͈̔͂���͂ݏo���Ƃ���ʓ��ɖ߂�
			}
		}

		if ((tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) && pos_.x != moveSpeed_) {		// D�L�[�������Ă���Ƃ�
			moveValue_.x = moveSpeed_;												// �E�ɍ��W���ړ�
			if (pos_.x >= play_Area_Size_Max.x - get_WIDTH()) {
				pos_.x = play_Area_Size_Max.x - get_WIDTH();						// ��ʂ͈̔͂���͂ݏo���Ƃ���ʓ��ɖ߂�
			}
		}

		// �����L�[��������Ă��Ȃ���Ԃł͉��̈ړ��ʂ�0�ɂ���
		if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_A) && !(tnl::Input::IsKeyDown(eKeys::KB_D)) ||
			tnl::Input::IsKeyReleaseTrigger(eKeys::KB_D) && !(tnl::Input::IsKeyDown(eKeys::KB_A))) {
			moveValue_.x = 0;
		}

		if (jumpCount_ < jumpMax_) {								// �W�����v�\�Ȏ��̂�

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX)) {
				PlaySoundMem(jumpSound_hdl_, DX_PLAYTYPE_BACK);
				moveValue_.y = -jumpPower_;							// �W�����v�̏���
				timeFall_ = 0;
				++jumpCount_;		// �W�����v�񐔂̃J�E���g�𑝂₷
			}
		}

	}
	else if (hp_ <= 0) {
		moveValue_.x = 0;
	}



	pos_ += moveValue_;										// �ړ��ʂ̉��Z

	if (pos_.y > play_Area_Size_Max.y - get_HEIGHT() / 2) {
		pos_.y = play_Area_Size_Max.y - get_HEIGHT() / 2;
		timeFall_ = 0;
		moveValue_.y = 0;
	}


	//DrawStringEx(100, 300, -1, "timeFall_ = %f", timeFall_);	// �������Ԃ̕\��

}

// hp�̒l���擾����֐�
const float& Player::get_hp_() {
	return hp_;
}

// hp�̒l��ύX����֐�
void Player::set_hp_(const float damage) {

	if (hitIntervalCount_ >= hitInterval_ || damage < 0) {

		if (damage > 0) {
			set_hitIntervalCount_(0);		// �_���[�W���󂯂Ă���̎��Ԃ�0�Ƀ��Z�b�g����
		}

		hp_ -= damage;
		PlaySoundMem(damageSound_hdl_, DX_PLAYTYPE_BACK);

	}

	if (hp_ > hpMax_)	hp_ = hpMax_;	// �̗͂��ő�l���傫���Ȃ������ő�l�ɖ߂�
	else if (hp_ < 0)	hp_ = 0;		// �̗͂�0��菬�����Ȃ����Ƃ�0�ɂ���
}

void Player::set_hitIntervalCount_(float time) {
	hitIntervalCount_ = time;
}


void Player::set_jumpCount_(int count) {
	jumpCount_ = count;
}
