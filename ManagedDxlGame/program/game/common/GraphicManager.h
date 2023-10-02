#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"

// �摜�̎��
enum class GRAPHIC_TYPE {
	AIR = 0,			// �����Ȃ�
	BLOCK,			// �u���b�N
	SPIKE,			// �j(��Q��)
	HEART,			// �n�[�g�̉摜
	BACK_GRASS		// �w�i�摜�F���� 
};


class GraphicManager {
private :
	GraphicManager();
	~GraphicManager() {};

	// �摜�̃A�h���X��csv�̓��e��ǂݍ��ޗp��vector
	std::vector<std::vector<std::string>> graphics_csv_;

	// �ǂݍ��񂾉摜��ۑ�����p��map
	std::unordered_map < GRAPHIC_TYPE, int> graphics_map_;

public :

	// GraphicManager���C���X�^���X������֐�
	static GraphicManager* GetInstance_();

	// �摜��ǂݍ��ފ֐�
	int loadGraph_(GRAPHIC_TYPE gpc_type);

	// �摜���폜����֐�
	void deleteGraph_(GRAPHIC_TYPE gpc_type);


	static void Destroy();

};