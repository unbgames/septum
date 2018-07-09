#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower (GameObject& go, Vec2 offset) :
		Component(go), offset(offset) {

}

void CameraFollower::Update (float dt) {
	associated.box.x = Camera::pos.x + offset.x;
	associated.box.y = Camera::pos.y + offset.y;
}

bool CameraFollower::Is (string type) const {
	return type == "CameraFollower";
}

void CameraFollower::Render () {

}
