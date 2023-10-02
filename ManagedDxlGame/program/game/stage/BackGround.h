#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class BackGround {
public :
	BackGround(int gpc_hdl);
	~BackGround();

	void update(float delta_time);
	void draw();

private :

	// �\��������W
	tnl::Vector3 pos_{DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0};

	// �w�i�摜�n���h��
	int gpc_hdl_ = 0;

};