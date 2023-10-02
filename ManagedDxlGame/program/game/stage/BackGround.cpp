#include "BackGround.h"


BackGround::BackGround(int gpc_hdl) {
	gpc_hdl_ = gpc_hdl;
}

BackGround::~BackGround() {

}


void BackGround::update(float delta_time) {

}

void BackGround::draw() {
	DrawRotaGraph(pos_.x, pos_.y, 2.0f, 0, gpc_hdl_, true);
}
