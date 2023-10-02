#include "AnimManager.h"

AnimManager::AnimManager() {
	anim_data_ = tnl::LoadCsv("csv/game/[000]common/AnimationData.csv");
}


// AnimManager���C���X�^���X��
AnimManager* AnimManager::GetInstance_() {
	static AnimManager* instance_ = nullptr;

	if (!instance_) {
		instance_ = new AnimManager();
	}
	return instance_;
}

std::vector<int> AnimManager::loadDivGraph(ANIM_CSV_OBJ ANIM_OBJ) {

	// file_path�ɑΉ�����摜�A�j���[�V�����n���h����T��
	auto it = animation_map_.find(ANIM_OBJ);
	

	if (it != animation_map_.end()) {
		return animation_map_[ANIM_OBJ];
	}

	// �摜�A�j���[�V�����̓ǂݍ���
	std::vector<int> anim_hdls(anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::TOTAL_FLAME)].getInt());
	LoadDivGraph(
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::PATH)].getString().c_str(),
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::TOTAL_FLAME)].getInt(),
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::HOLIZONTAL_FLAMES)].getInt(),
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::VERTICAL_FLAMES)].getInt(),
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::WIDTH)].getInt(),
		anim_data_[static_cast<int>(ANIM_OBJ)][static_cast<int>(ANIM_CSV_ARG::HEIGHT)].getInt(),
		anim_hdls.data());

	// �摜�A�j���[�V������animation_map_�Ƀp�X�ƕR�Â��ĕۑ�
	animation_map_.insert(std::make_pair(ANIM_OBJ, anim_hdls));


	// �A�j���[�V�����n���h����Ԃ�
	return anim_hdls;
}

// �摜���폜����֐�
void AnimManager::deleteAnimGraph(ANIM_CSV_OBJ ANIM_OBJ) {

	// ANIM_CSV_OBJ�ɑΉ�����摜�n���h����T��
	auto it = animation_map_.find(ANIM_OBJ);

	if (it != animation_map_.end()) {

		std::vector<int>& anim_hdls = it->second;

		for (int anim_hdl : anim_hdls) {
			DeleteGraph(anim_hdl);
		}


		// ANIM_CSV_OBJ�ɑΉ�����p�X���폜����
		if (it != animation_map_.end()) {
			animation_map_.erase(ANIM_OBJ);
		}

	}

}

