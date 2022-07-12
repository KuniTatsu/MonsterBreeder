#pragma once
#include"../dxlib_ext/dxlib_ext.h"

class Camera
{
public:
	Camera();
	~Camera();

	void CameraMove(tnl::Vector3& PlayerPos);

private:
	//カメラの中心座標
	tnl::Vector3 cameraPos = { 512,384,0 };

};

