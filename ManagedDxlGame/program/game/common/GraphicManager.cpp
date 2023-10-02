#include "GraphicManager.h"


GraphicManager::GraphicManager() {

	// �摜�A�h���X��csv�̓ǂݍ���
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

	// file_path�ɑΉ�����摜�n���h����T��
	auto it = graphics_map_.find(gpc_type);

	// ���Ƀ��[�h���Ă���ꍇ�A���̉摜�n���h����Ԃ�
	if (it != graphics_map_.end()) {
		return graphics_map_[gpc_type];
	}

	// �摜�̓ǂݍ���
	int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

	// graphics_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
	graphics_map_.insert(std::make_pair(gpc_type, gpc_hdl));

	// �摜�n���h����Ԃ�
	return gpc_hdl;

}

void GraphicManager::deleteGraph_(GRAPHIC_TYPE gpc_type) {

	// file_path�ɑΉ�����摜�n���h����T��
	auto it = graphics_map_.find(gpc_type);

	// �摜�n���h�������
	DeleteGraph(it->second);

	// file_path�̉摜�p�X���폜����
	if (it != graphics_map_.end()) {
		graphics_map_.erase(gpc_type);
	}

}

void GraphicManager::Destroy() {

	delete GetInstance_();
}
