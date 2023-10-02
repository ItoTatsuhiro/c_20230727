#include "CharacterBase.h"

const tnl::Vector3& CharacterBase::get_posPrev_() {
	return posPrev_;
}

const tnl::Vector3& CharacterBase::get_moveValue_() {
	return moveValue_;
}


void CharacterBase::set_moveValue_(const tnl::Vector3& newMoveVal) {
	moveValue_ = newMoveVal;
}

void CharacterBase::reset_timeFall_() {
	timeFall_ = 0;
}


