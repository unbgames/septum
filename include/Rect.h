#pragma once
#include "Vec2.h"
/**
 * Rect is a rectangle in a 2D-space
 */
class Rect {
	public:
		Rect ();
		/**
		 * Rect constructor
		 * @param x position on x-axis
		 * @param y position on y-axis
		 * @param w rectangle width
		 * @param h rectangle height
		 */
		Rect (float x, float y, float w, float h);
		/**
		 * Returns rectangle center
		 * @return center of rectangle
		 */
		Vec2 GetCenter () const;
		/**
		 * Returns distance between the center of two rectangles
		 * @param other other rectangle
		 * @return distance between two rectangles
		 */
		float GetDistance (const Rect other) const;
		/**
		 * Whether a rectangle contains a point
		 * @param x point x-axis coordinate
		 * @param y point y-axis coordinate
		 * @retval true the rectangle contains the point
		 * @retval false the rectangle doesn`t contain the point
		 */
		bool Contains (Vec2 point) const;

		Rect operator+ (const Vec2 vec) const;
		Rect& operator+= (const Vec2 vec);
		
		float x, y, w, h;
};
