#include "Background.h"
#include "Camera.h"

using std::string;

Background::Background (GameObject& associated, float parallax) :
		Component(associated), parallax(parallax){
}

Background::~Background () {
	layers.clear();
}

void Background::AddLayer (Sprite* spr) {
	layers.emplace_back(spr);
}

void Background::Render () {
	int layerNumber = 0;
	for (auto& layer : layers) {
		float posX = - Camera::pos.x * parallax * layerNumber;
		float posY = - Camera::pos.y * parallax * layerNumber;
		if(Camera::pos.x > 0) {
			if (posX < - layer->GetWidth()) {
				posX = - fmod(abs(posX), layer->GetWidth());
			}
			if (posY < - layer->GetHeight()) {
				posY = - fmod(abs(posY), layer->GetHeight());
			}
		} else {
			if (posX > layer->GetWidth()) {
				posX = fmod(abs(posX), layer->GetWidth());
			}
			if (posY > layer->GetHeight()) {
				posY = fmod(abs(posY), layer->GetHeight());
			}
		}
		layer->Render( posX, posY, true);
		layerNumber++;
	}
}

float Background::GetParallax () {
	return parallax;
}

void Background::SetParallax (float plx) {
	parallax = plx;
}

void Background::Update (float dt) {

}

bool Background::Is (string type) const {
	return (type == "Background");
}
