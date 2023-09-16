#include "GraphicManager.h"




GraphicManager* GraphicManager::GetInstance() {

	static GraphicManager* instance = nullptr;
	if (!instance) {
		instance = new GraphicManager();
	}
	return instance;
}

int GraphicManager::loadGraph(const std::string& file_path) {

	// file_path�ɑΉ�����摜�n���h����T��
	auto it = graphics_map_.find(file_path);

	// ���Ƀ��[�h���Ă���ꍇ�A���̉摜�n���h����Ԃ�
	if (it != graphics_map_.end()) {
		return graphics_map_[file_path];
	}

	// �摜�̓ǂݍ���
	int gpc_hdl = LoadGraph(file_path.c_str(), true);

	// graphics_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
	graphics_map_.insert(std::make_pair(file_path, gpc_hdl));

	// �摜�n���h����Ԃ�
	return gpc_hdl;

}

void GraphicManager::deleteGraph(const std::string& file_path) {

	// file_path�ɑΉ�����摜�n���h����T��
	auto it = graphics_map_.find(file_path);

	// �摜�n���h�������
	DeleteGraph(it->second);

	// file_path�̉摜�p�X���폜����
	if (it != graphics_map_.end()) {
		graphics_map_.erase(file_path);
	}

}
