#pragma once

/**
 * Vec2 is a vector in a 2D-space
 */
class Vec2 {
	public:
		Vec2 ();
		/**
		 * Vec2 constructor
		 * @param x position on x-axis
		 * @param y position on y-axis
		 */
		Vec2 (float x, float y);
		/**
		 * Returns the length(magnitude) of a vector
		 * @return vector length
		 */
		float GetLength () const;
		/**
		 * Return the unit vector of a vector
		 *
		 * An unit vector is a vector which has the same angle as nother vector but magnitude of 1
		 * @return unit vector
		 */
		Vec2 GetUnit () const;

		Vec2 operator+ (const Vec2 other) const;
		Vec2& operator+= (const Vec2 other);
		Vec2 operator- (const Vec2 other) const;
		Vec2& operator-= (const Vec2 other);
		Vec2 operator* (const int number) const;
		Vec2& operator*= (const int number);
		Vec2 operator* (const float number) const;
		Vec2& operator*= (const float number);

		/**
		 * Returns the distance between two points
		 * @param other the other point
		 * @return distance
		 */
		float GetDistance (const Vec2 other) const;
		/**
		 * Returns the angle of a Vector
		 * @return angle of the vector
		 */
		float GetAngle () const;
		/**
		 * Return the angle of a vector between 2 points
		 * @param other the other point
		 * @return angle of the vector
		 */
		float GetAngle (const Vec2 other) const;
		/**
		 * Returns the rotated vector
		 * @param angle angle of rotation
		 * @return rotated vector
		 */
		Vec2 GetRotated (float angle) const;

		float x, y;
};
