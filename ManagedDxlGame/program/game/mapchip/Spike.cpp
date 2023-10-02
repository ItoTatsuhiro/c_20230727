#include "Spike.h"


Spike::Spike(const tnl::Vector3& pos, MAPCHIP chipType) : MapChipBase(pos, chipType) {

	chipType_ = chipType;
	collision_ = false;
	has_damage_ = true;
	damageVal_ = 1.0f;
}

void Spike::onCollision_() {



}
