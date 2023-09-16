#include "GraphicManager.h"




GraphicManager* GraphicManager::GetInstance() {

	static GraphicManager* instance = nullptr;
	if (!instance) {
		instance = new GraphicManager();
	}
	return instance;
}

int GraphicManager::loadGraph(const std::string& file_path) {

	// file_pathに対応する画像ハンドルを探す
	auto it = graphics_map_.find(file_path);

	// 既にロードしてある場合、その画像ハンドルを返す
	if (it != graphics_map_.end()) {
		return graphics_map_[file_path];
	}

	// 画像の読み込み
	int gpc_hdl = LoadGraph(file_path.c_str(), true);

	// graphics_map_に読み込んだ画像をパスと紐づけて保存
	graphics_map_.insert(std::make_pair(file_path, gpc_hdl));

	// 画像ハンドルを返す
	return gpc_hdl;

}

void GraphicManager::deleteGraph(const std::string& file_path) {

	// file_pathに対応する画像ハンドルを探す
	auto it = graphics_map_.find(file_path);

	// 画像ハンドルを解放
	DeleteGraph(it->second);

	// file_pathの画像パスを削除する
	if (it != graphics_map_.end()) {
		graphics_map_.erase(file_path);
	}

}
