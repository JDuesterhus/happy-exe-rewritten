#pragma once
#include<cmath>
#include<ctime>

//some math stuff
#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846
#define M_PI_F		((float)(M_PI))
#define SQUARE( a ) a*a
#define DEG2RAD( x  )  ( (float)(x) * (float)( M_PI_F / 180.f ) )
#define RAD2DEG( x  )  ( (float)(x) * (float)( 180.f/M_PI_F ) )
#pragma warning(disable:4244)

//https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
//thanks A5 very cool
inline float FASTSQRT(float x) {
	unsigned int i = *(unsigned int*)& x;

	i += 127 << 23;
	i >>= 1;
	return *(float*)& i;
}



class Vector {
public:
	float x, y, z;

	Vector() {
		x = y = z = 0.0f;
	}

	Vector(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	Vector(float XYZ) {
		x = XYZ; y = XYZ; z = XYZ;
	}

	Vector(float* v) {
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector(const float* v) {
		x = v[0]; y = v[1]; z = v[2];
	}

	inline Vector& operator=(const Vector& v) {
		x = v.x; y = v.y; z = v.z; return *this;
	}

	inline Vector& operator=(const float* v) {
		x = v[0]; y = v[1]; z = v[2]; return *this;
	}

	inline float& operator[](int i) {
		return ((float*)this)[i];
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline Vector& operator*=(const Vector& v) {
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	inline Vector& operator/=(const Vector& v) {
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	inline Vector& operator+=(float v) {
		x += v; y += v; z += v; return *this;
	}

	inline Vector& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}

	inline Vector& operator/=(float v) {
		x /= v; y /= v; z /= v; return *this;
	}

	inline Vector operator-() const {
		return Vector(-x, -y, -z);
	}

	inline Vector operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	inline Vector operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	inline Vector operator*(const Vector& v) const {
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	inline Vector operator/(const Vector& v) const {
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	inline Vector operator+(float v) const {
		return Vector(x + v, y + v, z + v);
	}

	inline Vector operator-(float v) const {
		return Vector(x - v, y - v, z - v);
	}

	inline Vector operator*(float v) const {
		return Vector(x * v, y * v, z * v);
	}

	inline Vector operator/(float v) const {
		return Vector(x / v, y / v, z / v);
	}

	inline float Length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	inline float LengthSqr() const {
		return (x * x + y * y + z * z);
	}

	inline float LengthXY() const {
		return sqrtf(x * x + y * y);
	}

	inline float LengthXZ() const {
		return sqrtf(x * x + z * z);
	}

	inline float DistTo(const Vector& v) const {
		return (*this - v).Length();
	}

	inline float Dot(const Vector& v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

	inline Vector Cross(const Vector& v) const {
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	inline bool IsZero() const {
		return (x > -0.01f && x < 0.01f &&	y > -0.01f && y < 0.01f &&	z > -0.01f && z < 0.01f);
	}
};

