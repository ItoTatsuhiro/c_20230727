#include <algorithm>

#include "scene_Play.h"

ScenePlay::ScenePlay() {

	player_ = new Player(PLAY_AREA_SIZE_MAX, PLAY_AREA_SIZE_MIN);			// �v���C���[�̐���
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

	// �v���C���[��hp�����鎞�X�R�A�����Z
	if (player_->get_hp_() > 0) {
		ScoreManager::GetInstance_()->scoreCount_(delta_time);

		if (stage_ != nullptr) {
			stage_->update(delta_time);
		}

	}

	// �����蔻��̊m�F
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
	DrawStringEx(900, 100, 0, "SCORE�F%d", ScoreManager::GetInstance_()->get_nowScore_());

	if (player_->get_hp_() <= 0) {
		SetFontSize(100);
		DrawStringEx(350, 250, -1, "F I N I S H !");

		SetFontSize(45);
		DrawStringEx(450, 600, -1, "enter�L�[�Ō��ʔ��\��");
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
						player_->getPlayerPos(),		// �v���C���[�̍��W
						player_->get_moveValue_().x + player_->get_WIDTH(),			// �v���C���[�̉���(�ړ���+��)
						player_->get_moveValue_().y + player_->get_HEIGHT(),		// �v���C���[�̏c��(�ړ���+�c��)
						(*it)[y][x]->getPos_(),										// �}�b�v�`�b�v�̍��W
						stage_->get_mapchipSize_(),									// �}�b�v�`�b�v�̉���
						stage_->get_mapchipSize_())) {								// �}�b�v�`�b�v�̏c��

						player_->set_hp_((*it)[y][x]->get_damageVal_());			// �v���C���[�̗̑͂𒲐�����

					}
				}

				if ((*it)[y][x]->getCollision() == true) {


					// �}�b�v�`�b�v�ƃv���C���[�̏Փ˔���
					if (tnl::IsIntersectRect(
						player_->getPlayerPos(),		// �v���C���[�̍��W
						player_->get_moveValue_().x + player_->get_WIDTH(),			// �v���C���[�̉���(�ړ���+��)
						player_->get_moveValue_().y + player_->get_HEIGHT(),		// �v���C���[�̏c��(�ړ���+�c��)
						(*it)[y][x]->getPos_(),										// �}�b�v�`�b�v�̍��W
						stage_->get_mapchipSize_(),									// �}�b�v�`�b�v�̉���
						stage_->get_mapchipSize_())) {								// �}�b�v�`�b�v�̏c��


						float playerRight = player_->getPlayerPos().x + (player_->get_WIDTH() / 2);
						float playerBottom = player_->getPlayerPos().y + (player_->get_HEIGHT() / 2);
						float blockRight = (*it)[y][x]->getPos_().x + (stage_->get_mapchipSize_() / 2);
						float blockBottom = (*it)[y][x]->getPos_().y + (stage_->get_mapchipSize_() / 2);


						float overlap_x = 0.0f;					// �d�Ȃ��Ă���ʁFx
						float overlap_y = 0.0f;					// �d�Ȃ��Ă���ʁFy

						// overlap_x�̒l��ݒ�(�v���C���[�ƃu���b�N�̍��E���m�F)
						if (playerRight - ((*it)[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2) > blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2)) {

							overlap_x = blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2);
						}
						else {
							overlap_x = playerRight - ((*it)[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2);
						}

						// overlap_y�̒l��ݒ�(�v���C���[�ƃu���b�N�̏㉺���m�F)
						if (playerBottom - ((*it)[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2) > blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2)) {

							overlap_y = blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2);
						}
						else {

							overlap_y = playerBottom - ((*it)[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2);
						}

						if (overlap_x < overlap_y) {
							// X�������̏Փ�
							if (player_->getPlayerPos().x < (*it)[y][x]->getPos_().x) {
								// �v���C���[��������Փ�
								player_->setPlayerPos(player_->getPlayerPos() - tnl::Vector3(overlap_x, 0.0f, 0.0f));
							}
							else {
								// �v���C���[���E����Փ�
								player_->setPlayerPos(player_->getPlayerPos() + tnl::Vector3(overlap_x, 0.0f, 0.0f));
							}
							// X�������̑��x��0�ɐݒ�
							player_->set_moveValue_(tnl::Vector3(0, player_->get_moveValue_().y, 0));

						}
						else {
							// Y�������̏Փ�
							if (player_->getPlayerPos().y < (*it)[y][x]->getPos_().y) {

								// �v���C���[���ォ��Փ�
								player_->setPlayerPos(player_->getPlayerPos() - tnl::Vector3(0.0f, overlap_y, 0.0f));

								// �������Ԃ����Z�b�g
								player_->reset_timeFall_();

							}
							else {

								// �v���C���[��������Փ�
								player_->setPlayerPos(player_->getPlayerPos() + tnl::Vector3(0.0f, overlap_y, 0.0f));
							}

							// Y�������̑��x��0�ɐݒ�
							player_->set_moveValue_(tnl::Vector3(player_->get_moveValue_().x, 0, 0));

						}

						// �����Ńv���C���[�̃W�����v�񐔂��񕜂����� 
						//DrawStringEx(500, 700, -1, "hit");


						// �ڒn�����ۂɃW�����v�񐔂��񕜂�����
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


// �v���C�V�[���̏I�����̏���
void ScenePlay::sceneplayFin_() {


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_MAX)) {
		auto mgr = GameManager::GetInstance_();
		mgr->changeScene(new SceneResult());
	}

}