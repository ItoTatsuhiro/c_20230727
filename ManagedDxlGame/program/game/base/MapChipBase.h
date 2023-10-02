#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// �}�b�v�`�b�v�Ɏg�p����p�̒萔
enum class MAPCHIP {
	AIR,			// 0�F�z�u�Ȃ�
	BLOCK,			// 1�F�n��
	SPIKE,			// 2�F��Q��(��)
	MAX				// �}�b�v�`�b�v�̎�ނ̑���
};


class MapChipBase {
public :

	MapChipBase( const tnl::Vector3& pos, MAPCHIP chipType);
	virtual ~MapChipBase();

	// �����蔻��̗L�����擾����
	bool& getCollision();

	// ���W���擾����
	tnl::Vector3& getPos_();

	// ���W��ύX����֐�
	void setPos_(const tnl::Vector3& newPos);

	// �_���[�W�̗L�����擾����֐�
	const bool& get_has_damage_();

	// �_���[�W�̒l���擾����֐�
	const float& get_damageVal_();

	// �`�b�v�̎�ނ��擾���邽�߂̊֐�
	MAPCHIP get_chipType_();

	// �I�u�W�F�N�g�ƐڐG�����ۂ̏���
	virtual void onCollision_() = 0 {};


protected :

	MAPCHIP chipType_ = MAPCHIP::AIR;	// �`�b�v�̎��
	bool collision_ = true;		// �����蔻��̗L��
	bool has_damage_ = false;	// �ڐG���̃_���[�W�̗L��
	float damageVal_ = 0;		// �_���[�W�̒l
	tnl::Vector3 pos_;			// �z�u����Ă�����W


};

