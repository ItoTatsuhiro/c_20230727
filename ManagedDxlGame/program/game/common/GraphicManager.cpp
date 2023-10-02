#include "GraphicManager.h"


GraphicManager::GraphicManager() {

	// 画像アドレスのcsvの読み込み
	graphics_csv_ = tnl::LoadCsv<std::string>("csv/game/[000]common/GraphAddress.csv");
}


GraphicManager* GraphicManager::GetInstance_() {

	static GraphicManager* instance = nullptr;
	if (!instance) {
		instance = new GraphicManager();
	}
	return instance;
}

int GraphicManager::loadGraph_(GRAPHIC_TYPE gpc_type) {

	// file_pathに対応する画像ハンドルを探す
	auto it = graphics_map_.find(gpc_type);

	// 既にロードしてある場合、その画像ハンドルを返す
	if (it != graphics_map_.end()) {
		return graphics_map_[gpc_type];
	}

	// 画像の読み込み
	int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

	// graphics_map_に読み込んだ画像をパスと紐づけて保存
	graphics_map_.insert(std::make_pair(gpc_type, gpc_hdl));

	// 画像ハンドルを返す
	return gpc_hdl;

}

void GraphicManager::deleteGraph_(GRAPHIC_TYPE gpc_type) {

	// file_pathに対応する画像ハンドルを探す
	auto it = graphics_map_.find(gpc_type);

	// 画像ハンドルを解放
	DeleteGraph(it->second);

	// file_pathの画像パスを削除する
	if (it != graphics_map_.end()) {
		graphics_map_.erase(gpc_type);
	}

}

void GraphicManager::Destroy() {

	delete GetInstance_();
}
