#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::CameraMove(tnl::Vector3& PlayerPos)
{
	//70*32はマップの横幅 いずれ引数かポインタに変える
	if (PlayerPos.x > 1024 / 2 && PlayerPos.x < 70 * 32 - 1024 / 2 + 32) {
		cameraPos.x = PlayerPos.x - (1024 / 2);
	}

	if (PlayerPos.y > 768 / 2 && PlayerPos.y < 40 * 32 - 768 / 2 + 32) {
		cameraPos.y = PlayerPos.y - (768 / 2);
	}

}
