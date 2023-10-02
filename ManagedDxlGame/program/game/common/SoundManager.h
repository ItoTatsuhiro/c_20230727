#pragma once
#include <string>
#include <unordered_map>
#include "../../dxlib_ext/dxlib_ext.h"

// �摜�̎��
enum class SOUND_KINDS {
	TITLE,		// �^�C�g��BGM
	PLAY,		// �v���C�V�[��BGM
	RESULT,		// ���U���gBGM
	JUMP,		// �W�����v���ʉ�
	RESULT_DIS,	// ���U���g�\�����ʉ�
	DAMAGE		// ��_���[�W
};


class SoundManager {
private:
	SoundManager();
	~SoundManager() {};

	// �摜�̃A�h���X��csv�̓��e��ǂݍ��ޗp��vector
	std::vector<std::vector<std::string>> sounds_csv_;

	// �ǂݍ��񂾉摜��ۑ�����p��map
	std::unordered_map < SOUND_KINDS, int> sounds_map_;

public:

	// SoundManager���C���X�^���X������֐�
	static SoundManager* GetInstance_();

	// �摜��ǂݍ��ފ֐�
	int loadSoundMem_(SOUND_KINDS sound_type);

	// �摜���폜����֐�
	void deleteSoundMem_(SOUND_KINDS sound_type);


	static void Destroy();

};