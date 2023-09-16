#include "MapChipBase.h"

MapChipBase::MapChipBase(const tnl::Vector3& pos, MAPCHIP chipType) : pos_(pos), chipType_(chipType) {

}

MapChipBase::~MapChipBase() {

}

// 衝突判定の有無を取得する関数
bool& MapChipBase::getCollision() {
	return collision_;
}

// 座標を取得する用の関数
tnl::Vector3& MapChipBase::getPos_() {
	return pos_;
}
