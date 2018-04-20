#include "Vec2.h"
#include <math.h>

Vec2::Vec2 () :
		x(0), y(0) {
}
Vec2::Vec2 (float x, float y) :
		x(x), y(y) {
}
float Vec2::GetLength () const {
	return sqrt(x * x + y * y);
}
Vec2 Vec2::GetUnit () const {
	return Vec2(x / GetLength(), y / GetLength());
}
Vec2 Vec2::operator+ (const Vec2 other) const {
	return Vec2(x + other.x, y + other.y);
}
Vec2& Vec2::operator+= (const Vec2 other) {
	x += other.x;
	y += other.y;
	return *this;
}
Vec2 Vec2::operator- (const Vec2 other) const {
	return Vec2(x - other.x, y - other.y);
}
Vec2& Vec2::operator-= (const Vec2 other) {
	x -= other.x;
	y -= other.y;
	return *this;
}
Vec2 Vec2::operator* (const int number) const {
	return Vec2(x * number, y * number);
}
Vec2& Vec2::operator*= (const int number) {
	x *= number;
	y *= number;
	return *this;
}
Vec2 Vec2::operator* (const float number) const {
	return Vec2(x * number, y * number);
}
Vec2& Vec2::operator*= (const float number) {
	x *= number;
	y *= number;
	return *this;
}
float Vec2::GetDistance (const Vec2 other) const {
	Vec2 diff = *this - other;
	return diff.GetLength();
}
float Vec2::GetAngle () const {
	return atan2(y, x);
}
float Vec2::GetAngle (const Vec2 other) const {
	Vec2 diff = *this - other;
	return diff.GetAngle();
}
Vec2 Vec2::GetRotated (float angle) const {
	return Vec2(x * cos(angle) - y * sin(angle),
			y * cos(angle) + x * sin(angle));
}
