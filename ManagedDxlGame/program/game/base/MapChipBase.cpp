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

void MapChipBase::setPos_(const tnl::Vector3& newPos) {
	
	pos_ = newPos;

}

// ダメージの有無を取得する関数
const bool& MapChipBase::get_has_damage_() {
	return has_damage_;
}

// ダメージの値を取得する関数
const float& MapChipBase::get_damageVal_() {
	return damageVal_;
}


// チップの種類を取得する関数
MAPCHIP MapChipBase::get_chipType_() {
	return chipType_;
}
