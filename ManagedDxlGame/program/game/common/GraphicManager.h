#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"

// 画像の種類
enum class GRAPHIC_TYPE {
	AIR = 0,			// 何もなし
	BLOCK,			// ブロック
	SPIKE,			// 針(障害物)
	HEART,			// ハートの画像
	BACK_GRASS		// 背景画像：草原 
};


class GraphicManager {
private :
	GraphicManager();
	~GraphicManager() {};

	// 画像のアドレスのcsvの内容を読み込む用のvector
	std::vector<std::vector<std::string>> graphics_csv_;

	// 読み込んだ画像を保存する用のmap
	std::unordered_map < GRAPHIC_TYPE, int> graphics_map_;

public :

	// GraphicManagerをインスタンス化する関数
	static GraphicManager* GetInstance_();

	// 画像を読み込む関数
	int loadGraph_(GRAPHIC_TYPE gpc_type);

	// 画像を削除する関数
	void deleteGraph_(GRAPHIC_TYPE gpc_type);


	static void Destroy();

};