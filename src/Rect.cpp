#include "Rect.h"

Rect::Rect () :
		x(0), y(0), w(0), h(0) {
}

Rect::Rect (float x, float y, float w, float h) :
		x(x), y(y), w(w), h(h) {
	
}

bool Rect::Contains (Vec2 point) const {
	return (point.x >= x && point.x <= x + w)
			&& (point.y >= y && point.y <= y + h);
}

Vec2 Rect::GetCenter () const {
	return Vec2(x + w / 2.0, y + h / 2.0);
}

float Rect::GetDistance (Rect other) const {
	return GetCenter().GetDistance(other.GetCenter());
}

Rect Rect::operator+ (const Vec2 vec) const {
	return Rect(x, y, w + vec.x, h + vec.y);
}

Rect& Rect::operator+= (const Vec2 vec) {
	w += vec.x;
	h += vec.y;
	return *this;
}
