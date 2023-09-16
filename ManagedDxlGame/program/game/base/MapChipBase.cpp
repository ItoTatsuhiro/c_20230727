#include "MapChipBase.h"

MapChipBase::MapChipBase(const tnl::Vector3& pos, MAPCHIP chipType) : pos_(pos), chipType_(chipType) {

}

MapChipBase::~MapChipBase() {

}

// Õ“Ë”»’è‚Ì—L–³‚ğæ“¾‚·‚éŠÖ”
bool& MapChipBase::getCollision() {
	return collision_;
}

// À•W‚ğæ“¾‚·‚é—p‚ÌŠÖ”
tnl::Vector3& MapChipBase::getPos_() {
	return pos_;
}
