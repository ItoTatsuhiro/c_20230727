#include "MapChipBase.h"

MapChipBase::MapChipBase(const tnl::Vector3& pos, MAPCHIP chipType) : pos_(pos), chipType_(chipType) {

}

MapChipBase::~MapChipBase() {

}

// �Փ˔���̗L�����擾����֐�
bool& MapChipBase::getCollision() {
	return collision_;
}

// ���W���擾����p�̊֐�
tnl::Vector3& MapChipBase::getPos_() {
	return pos_;
}

void MapChipBase::setPos_(const tnl::Vector3& newPos) {
	
	pos_ = newPos;

}

// �_���[�W�̗L�����擾����֐�
const bool& MapChipBase::get_has_damage_() {
	return has_damage_;
}

// �_���[�W�̒l���擾����֐�
const float& MapChipBase::get_damageVal_() {
	return damageVal_;
}


// �`�b�v�̎�ނ��擾����֐�
MAPCHIP MapChipBase::get_chipType_() {
	return chipType_;
}
