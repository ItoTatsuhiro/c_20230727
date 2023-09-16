#include <algorithm>

#include "scene_Play.h"

ScenePlay::ScenePlay() {

	player_ = new Player(PLAY_AREA_SIZE_MAX, PLAY_AREA_SIZE_MIN);			// �v���C���[�̐���
	stage_ = new Stage();

}

ScenePlay::~ScenePlay() {

	delete player_;
	player_ = nullptr;

}

void ScenePlay::update(float delta_time) {

	if (player_ != nullptr) {
		player_->update(delta_time);
	}
	if (stage_ != nullptr) {
		stage_->update(delta_time);
	}

	hitCheck();
}

void ScenePlay::draw() {

	if (player_ != nullptr) player_->draw();
	if (stage_ != nullptr) stage_->draw();

	DrawStringEx(100, 100, -1, "Play");


	//if (player_) {
	//	DrawStringEx(100, 150, -1, "pos_.x = %d", player_->pos_.x);
	//	DrawStringEx(100, 200, -1, "pos_.y = %d", player_->pos_.y);
	//}
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

	std::vector<std::vector<MapChipBase*>> stageMap = stage_->get_stageMap_Obj_();

	DrawStringEx(500, 100, -1, "PlayerPos = %f, %f", player_->getPlayerPos().x, player_->getPlayerPos().y);


	for (int y = 0; y < stage_->get_stageCutNumber_().y; ++y) {
 		for (int x = 0; x < stage_->get_stageCutNumber_().x; ++x) {

			if (stageMap[y][x] == nullptr) continue;

			if (stage_->get_stageMap_Obj_()[y][x]->getCollision() == true) {


				// �}�b�v�`�b�v�ƃv���C���[�̏Փ˔���
				if (tnl::IsIntersectRect(
					player_->getPlayerPos(),		// �v���C���[�̍��W
					player_->get_moveValue_().x + player_->get_WIDTH(),			// �v���C���[�̉���(�ړ���+��)
					player_->get_moveValue_().y + player_->get_HEIGHT(),		// �v���C���[�̏c��(�ړ���+�c��)
					stageMap[y][x]->getPos_(),									// �}�b�v�`�b�v�̍��W
					stage_->get_mapchipSize_(),									// �}�b�v�`�b�v�̉���
					stage_->get_mapchipSize_())) {								// �}�b�v�`�b�v�̏c��

					// //�����̓����蔻��̏������C������
					//player_->setPlayerPos(player_->get_posPrev_());
					//DrawStringEx(500, 700, -1, "hit");

					float playerRight = player_->getPlayerPos().x + (player_->get_WIDTH() / 2);
					float playerBottom = player_->getPlayerPos().y + (player_->get_HEIGHT() / 2);
					float blockRight = stageMap[y][x]->getPos_().x + (stage_->get_mapchipSize_() / 2);
					float blockBottom = stageMap[y][x]->getPos_().y + (stage_->get_mapchipSize_() / 2);


					float overlap_x = 0.0f;					// �d�Ȃ��Ă���ʁFx
					float overlap_y = 0.0f;					// �d�Ȃ��Ă���ʁFy

					// overlap_x�̒l��ݒ�(�v���C���[�ƃu���b�N�̍��E���m�F)
					if (playerRight - (stageMap[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2) > blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2)) {

						overlap_x = blockRight - (player_->getPlayerPos().x - stage_->get_mapchipSize_() / 2);
					}
					else {
						overlap_x = playerRight - (stageMap[y][x]->getPos_().x - stage_->get_mapchipSize_() / 2);
					}

					// overlap_y�̒l��ݒ�(�v���C���[�ƃu���b�N�̏㉺���m�F)
					if (playerBottom - (stageMap[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2) > blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2)) {
						
						overlap_y = blockBottom - (player_->getPlayerPos().y - player_->get_HEIGHT() / 2);
					}
					else {

						overlap_y = playerBottom - (stageMap[y][x]->getPos_().y - stage_->get_mapchipSize_() / 2);
					}

					if (overlap_x < overlap_y) {
						// X�������̏Փ�
						if (player_->getPlayerPos().x < stageMap[y][x]->getPos_().x) {
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
						if (player_->getPlayerPos().y < stageMap[y][x]->getPos_().y) {

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

					DrawStringEx(500, 700, -1, "hit");
				}

			
			}
		}
	}
}

