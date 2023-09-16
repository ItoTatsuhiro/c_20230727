#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// �}�b�v�`�b�v�Ɏg�p����p�̒萔
enum class MAPCHIP {
	AIR,			// 0�F�z�u�Ȃ�
	BLOCK,			// 1�F�n��
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



protected :

	MAPCHIP chipType_ = MAPCHIP::AIR;	// �`�b�v�̎��
	bool collision_ = true;		// �����蔻��̗L��
	tnl::Vector3 pos_;			// �z�u����Ă�����W


};

