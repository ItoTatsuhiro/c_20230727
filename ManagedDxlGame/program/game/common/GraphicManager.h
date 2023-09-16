#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"
//#include "../object/Stage.h"


class GraphicManager {
private :
	GraphicManager() {};
	~GraphicManager() {};

	// �ǂݍ��񂾉摜��ۑ�����p��map
	std::unordered_map < std::string, int> graphics_map_;

public :

	// GraphicManager���C���X�^���X������֐�
	static GraphicManager* GetInstance();

	// �摜��ǂݍ��ފ֐�
	int loadGraph(const std::string& file_path);

	// �摜���폜����֐�
	void deleteGraph(const std::string& file_path);


	static void Destroy();

};