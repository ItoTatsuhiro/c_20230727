#include "SoundManager.h"

SoundManager::SoundManager() {

	// サウンドアドレスのcsvの読み込み
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

	// SOUND_KINDSに対応するサウンドハンドルを探す
	auto it = sounds_map_.find(sound_type);

	// 既にロードしてある場合、そのサウンドハンドルを返す
	if (it != sounds_map_.end()) {
		return sounds_map_[sound_type];
	}

	// サウンドの読み込み
	int sound_hdl = LoadSoundMem(sounds_csv_[static_cast<int>(sound_type)][1].c_str(), true);

	// sounds_map_に読み込んだ画像をパスと紐づけて保存
	sounds_map_.insert(std::make_pair(sound_type, sound_hdl));

	// サウンドハンドルを返す
	return sound_hdl;

}

void SoundManager::deleteSoundMem_(SOUND_KINDS sound_type) {

	// SOUND_KINDSに対応する画像ハンドルを探す
	auto it = sounds_map_.find(sound_type);


	// サウンドハンドルを解放
	DeleteSoundMem(it->second);

	// SOUND_KINDSに対応するパスを削除する
	if (it != sounds_map_.end()) {
		sounds_map_.erase(sound_type);
	}

}

void SoundManager::Destroy() {

	delete GetInstance_();
}
