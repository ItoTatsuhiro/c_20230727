#include "SoundManager.h"

SoundManager::SoundManager() {

	// �T�E���h�A�h���X��csv�̓ǂݍ���
	sounds_csv_ = tnl::LoadCsv<std::string>("csv/game/[000]common/SoundManager.csv");
}


SoundManager* SoundManager::GetInstance_() {

	static SoundManager* instance = nullptr;
	if (!instance) {
		instance = new SoundManager();
	}
	return instance;
}

int SoundManager::loadSoundMem_(SOUND_KINDS sound_type){

	// SOUND_KINDS�ɑΉ�����T�E���h�n���h����T��
	auto it = sounds_map_.find(sound_type);

	// ���Ƀ��[�h���Ă���ꍇ�A���̃T�E���h�n���h����Ԃ�
	if (it != sounds_map_.end()) {
		return sounds_map_[sound_type];
	}

	// �T�E���h�̓ǂݍ���
	int sound_hdl = LoadSoundMem(sounds_csv_[static_cast<int>(sound_type)][1].c_str(), true);

	// sounds_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
	sounds_map_.insert(std::make_pair(sound_type, sound_hdl));

	// �T�E���h�n���h����Ԃ�
	return sound_hdl;

}

void SoundManager::deleteSoundMem_(SOUND_KINDS sound_type) {

	// SOUND_KINDS�ɑΉ�����摜�n���h����T��
	auto it = sounds_map_.find(sound_type);


	// �T�E���h�n���h�������
	DeleteSoundMem(it->second);

	// SOUND_KINDS�ɑΉ�����p�X���폜����
	if (it != sounds_map_.end()) {
		sounds_map_.erase(sound_type);
	}

}

void SoundManager::Destroy() {

	delete GetInstance_();
}
