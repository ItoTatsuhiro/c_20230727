#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"

// アニメーションのcsvの項目(x方向)
enum class ANIM_CSV_ARG {
	PATH = 1,				// 画像のパス
	TOTAL_FLAME,			// 総分割数
	HOLIZONTAL_FLAMES,		// 横方向の分割数
	VERTICAL_FLAMES,		// 縦方向の分割数
	WIDTH,					// 一つ当たりの横幅
	HEIGHT,					// 一つ当たりの高さ
	MAX						// 項目の数+1
};

// アニメーションのcsvのオブジェクト(y方向)
enum class ANIM_CSV_OBJ {
	PLAYER = 1,					// プレイヤーのアニメーション
	MAX
};

class AnimManager {
private :

	AnimManager();
	~AnimManager() {};

	// 読み込んだアニメーション画像を保存する用のmap
	std::unordered_map < ANIM_CSV_OBJ, std::vector<int> > animation_map_;

public :

	std::vector<std::vector<tnl::CsvCell>> anim_data_;

	// アニメーションマネージャーをインスタンス化する関数
	static AnimManager* GetInstance_();

	// アニメーション画像を読み込む関数
	std::vector<int> loadDivGraph(ANIM_CSV_OBJ ANIM_OBJ);

	// 画像を削除する関数
	void deleteAnimGraph(ANIM_CSV_OBJ ANIM_OBJ);

	// インスタンス化したクラスを削除する関数
	static void Destroy();

};