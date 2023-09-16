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
