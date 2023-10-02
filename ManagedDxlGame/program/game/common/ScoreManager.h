#pragma once

class ScoreManager {
private:
	ScoreManager();
	~ScoreManager();

	int nowScore_ = 0;			// ���ݎ��s���̃Q�[���̃X�R�A
	int highScore_ = 0;			// �ߋ��ō��X�R�A

	float scoreAddTime_ = 0.5f;								// �X�R�A�����Z���鎞��

	int scoreAddTime_Value_ = 100;							// �X�R�A�̉��Z��񓖂���̉��Z�����X�R�A�̗�

public:

	// �X�R�A�}�l�[�W���[���C���X�^���X�����邽�߂̊֐�
	static ScoreManager* GetInstance_();

	const int& get_nowScore_() { return nowScore_; }			// ���݂̃Q�[���̃X�R�A���擾����֐�
	const int& get_highScore_() { return highScore_; }		// �ߋ��ō��X�R�A���擾����֐�

	void scoreCount_(float delta_time);						// �X�R�A�����Z����p�̊֐�

	void scoreReset();										// �X�R�A������������֐�
	void highScoreUpdate();									// �ō��X�R�A���X�V����ۂɎg�p����֐�
};