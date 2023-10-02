#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class BackGround {
public :
	BackGround(int gpc_hdl);
	~BackGround();

	void update(float delta_time);
	void draw();

private :

	// 表示する座標
	tnl::Vector3 pos_{DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0};

	// 背景画像ハンドル
	int gpc_hdl_ = 0;

};