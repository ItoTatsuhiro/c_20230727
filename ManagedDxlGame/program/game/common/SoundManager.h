#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"

// 画像の種類
enum class SOUND_KINDS {
	TITLE,		// タイトルBGM
	PLAY,		// プレイシーンBGM
	RESULT,		// リザルトBGM
	JUMP,		// ジャンプ効果音
	RESULT_DIS,	// リザルト表示効果音
	DAMAGE		// 被ダメージ
};


class SoundManager {
private:
	SoundManager();
	~SoundManager() {};

	// 画像のアドレスのcsvの内容を読み込む用のvector
	std::vector<std::vector<std::string>> sounds_csv_;

	// 読み込んだ画像を保存する用のmap
	std::unordered_map < SOUND_KINDS, int> sounds_map_;

public:

	// SoundManagerをインスタンス化する関数
	static SoundManager* GetInstance_();

	// 画像を読み込む関数
	int loadSoundMem_(SOUND_KINDS sound_type);

	// 画像を削除する関数
	void deleteSoundMem_(SOUND_KINDS sound_type);


	static void Destroy();

};