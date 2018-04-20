#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower (GameObject& go) :
		Component(go) {
	
}

void CameraFollower::Update (float dt) {
	associated.box.x = Camera::pos.x;
	associated.box.y = Camera::pos.y;
}

bool CameraFollower::Is (string type) const {
	return type == "CameraFollower";
}

void CameraFollower::Render () {

}
