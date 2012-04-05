#ifndef __UTIL_VECTOR_H__
#define __UTIL_VECTOR_H__

namespace Util
{
	class Vec3
	{
	public:
		float x;
		float y;
		float z;
		
		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		inline Vec3 operator+(const Vec3& rhs) { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
		inline Vec3 operator*(const float scale) { return Vec3(x * scale, y * scale, z * scale); }
	};
};

#endif /*__UTIL_VECTOR_H__*/