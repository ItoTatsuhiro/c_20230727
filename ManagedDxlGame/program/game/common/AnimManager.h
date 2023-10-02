#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"

// �A�j���[�V������csv�̍���(x����)
enum class ANIM_CSV_ARG {
	PATH = 1,				// �摜�̃p�X
	TOTAL_FLAME,			// ��������
	HOLIZONTAL_FLAMES,		// �������̕�����
	VERTICAL_FLAMES,		// �c�����̕�����
	WIDTH,					// �������̉���
	HEIGHT,					// �������̍���
	MAX						// ���ڂ̐�+1
};

// �A�j���[�V������csv�̃I�u�W�F�N�g(y����)
enum class ANIM_CSV_OBJ {
	PLAYER = 1,					// �v���C���[�̃A�j���[�V����
	MAX
};

class AnimManager {
private :

	AnimManager();
	~AnimManager() {};

	// �ǂݍ��񂾃A�j���[�V�����摜��ۑ�����p��map
	std::unordered_map < ANIM_CSV_OBJ, std::vector<int> > animation_map_;

public :

	std::vector<std::vector<tnl::CsvCell>> anim_data_;

	// �A�j���[�V�����}�l�[�W���[���C���X�^���X������֐�
	static AnimManager* GetInstance_();

	// �A�j���[�V�����摜��ǂݍ��ފ֐�
	std::vector<int> loadDivGraph(ANIM_CSV_OBJ ANIM_OBJ);

	// �摜���폜����֐�
	void deleteAnimGraph(ANIM_CSV_OBJ ANIM_OBJ);

	// �C���X�^���X�������N���X���폜����֐�
	static void Destroy();

};