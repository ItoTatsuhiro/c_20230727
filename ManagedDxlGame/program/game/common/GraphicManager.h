#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"
//#include "../object/Stage.h"


class GraphicManager {
private :
	GraphicManager() {};
	~GraphicManager() {};

	// 読み込んだ画像を保存する用のmap
	std::unordered_map < std::string, int> graphics_map_;

public :

	// GraphicManagerをインスタンス化する関数
	static GraphicManager* GetInstance();

	// 画像を読み込む関数
	int loadGraph(const std::string& file_path);

	// 画像を削除する関数
	void deleteGraph(const std::string& file_path);


	static void Destroy();

};