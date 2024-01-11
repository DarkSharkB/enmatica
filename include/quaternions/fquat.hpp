/* Single Precision Floating-Point Quaternions
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vectors/fvec3.hpp"
#include "../matrices/fmat4x4.hpp"
#include "../empch.hpp"

struct fquat
{
	union
	{
		struct 
		{
			flt32 w;
			flt32 x;
			flt32 y;
			flt32 z;
		};
		flt32 arr[4];
	};

public:
	fquat(const fquat &qt);
	fquat(const flt32 val = 0.0f);
	fquat(const flt32 fw, const flt32 fx, const flt32 fy = 0.0f, const flt32 fz = 0.0f);
	fquat(const flt32 w, const vec3 xyz);
	
	fquat operator+(const fquat other);
	fquat operator+=(const fquat other);
	fquat operator-();
	fquat operator-(const fquat other);
	fquat operator-=(const fquat other);
	fquat operator*(const fquat &other);
	fquat operator*(const flt32 val);
	fquat operator*=(const flt32 val);
	fquat operator/(const flt32 val);
	fquat operator/=(const flt32 val);

	flt32 Dot(const fquat &other);

	static fquat Conjugate(const fquat &q);
	static fquat Normalise(fquat q);
	static fquat Inverse(const fquat &q);
	static fquat Rotate(flt32 angle, const vec3 &axis);
	static fquat ToQuaternion(vec3 rot);
	static vec3 ToEulerAngles(const fquat &qt);
	static mat4x4 ToRotationMatrix(const fquat &qt);

	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fquat qt)
	{
		os << "( W: " << qt.w << "\tX: " << qt.x << "\tY: " << qt.y << "\tZ: " << qt.z << " )";

		return os;
	}
	#endif
};

#ifdef ENMATICA_IMPL
	fquat::fquat(const fquat &qt)
	{
		*this = qt;
	}

	fquat::fquat(const flt32 val) : x(val), y(val), z(val) {
		w = 1.0f;
	}

	fquat::fquat(const flt32 fw, const flt32 fx, const flt32 fy, const flt32 fz) : w(fw), x(fx), y(fy), z(fz) {}

	fquat::fquat(const flt32 w, const vec3 xyz)
	{
		this->w = w;
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
	}

	fquat fquat::operator+(const fquat other)
	{
		return { this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z };
	}

	fquat fquat::operator+=(const fquat other)
	{
		this->w += other.w;
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	fquat fquat::operator-()
	{
		return { -this->w, -this->x, -this->y, -this->z };
	}

	fquat fquat::operator-(const fquat other)
	{
		return { this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z };
	}

	fquat fquat::operator-=(const fquat other)
	{
		this->w -= other.w;
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	fquat fquat::operator*(const fquat &other)
	{
		return 
		{
			this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
			this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
			this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
			this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
		};
	}

	fquat fquat::operator*(const flt32 val)
	{
		return { w * val, x * val, y * val, z * val };
	}

	fquat fquat::operator*=(const flt32 val)
	{
		this->w *= val;
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return *this;
	}

	fquat fquat::operator/(const flt32 val)
	{
		const flt32 div = 1.0f / val;

		return { w * div, x * div, y * div, z * div };
	}

	fquat fquat::operator/=(const flt32 val)
	{
		const flt32 div = 1.0f / val;

		this->w *= div;
		this->x *= div;
		this->y *= div;
		this->z *= div;

		return *this;
	}

	flt32 fquat::Dot(const fquat &other)
	{
		return this->w * other.w + this->x * other.x + this->y * other.y + this->z * other.z;
	}

	fquat fquat::Conjugate(const fquat &q)
	{
		return { q.w, -q.x, -q.y, -q.z };
	}

	fquat fquat::Normalise(fquat q)
	{
		const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

		return q / mag;
	}

	fquat fquat::Inverse(const fquat &q)
	{
		const flt32 mag2 = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;

		return fquat::Conjugate(q) / mag2;
	}
	
	fquat fquat::Rotate(flt32 angle, const vec3 &axis)
	{
		const flt32 hang = angle * 0.5f;
		const flt32 cosha = cos(hang);
		const flt32 sinha = sin(hang);

		return { cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z };
	}

	fquat fquat::ToQuaternion(vec3 eulerAngles)
	{
		const vec3 heuler = eulerAngles * 0.5f;	// A little SIMD optimisation, not much

		const flt32 cr = cos(heuler.x);
		const flt32 cp = cos(heuler.y);
		const flt32 cy = cos(heuler.z);

		const flt32 sr = sin(heuler.x);
		const flt32 sp = sin(heuler.y);
		const flt32 sy = sin(heuler.z);

		return
		{
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		};
	}

	vec3 fquat::ToEulerAngles(const fquat &qt)
	{
		const flt32 y2 = qt.y * qt.y;
		const flt32 wysxz2 = 2 * (qt.w * qt.y - qt.x * qt.z);

		// X-axis Rotation
		const flt32 sinr_cosp = 2 * (qt.w * qt.x + qt.y * qt.z);
		const flt32 cosr_cosp = 1 - 2 * (qt.x * qt.x + y2);
		const flt32 r = std::atan2(sinr_cosp, cosr_cosp);

		// Y-axis Rotation
		/*flt32 sinp = std::sqrt(1 + wysxz2);
		flt32 cosp = std::sqrt(1 - wysxz2);
		flt32 p = 2 * std::atan2(sinp, cosp) - pi / 2;*/	// Original

		const flt32 p = std::asin(wysxz2);	// Alternative - hope it's same

		// Z-axis Rotation
		const flt32 siny_cosp = 2 * (qt.w * qt.z + qt.x * qt.y);
		const flt32 cosy_cosp = 1 - 2 * (y2 + qt.z * qt.z);
		const flt32 y = std::atan2(siny_cosp, cosy_cosp);

		return { r, p, y };
	}

	mat4x4 fquat::ToRotationMatrix(const fquat &qt)
	{
		const flt32 x2 = qt.x * qt.x;
		const flt32 y2 = qt.y * qt.y;
		const flt32 z2 = qt.z * qt.z;

		const flt32 xy = qt.x * qt.y;
		const flt32 zw = qt.w * qt.z;

		const flt32 xz = qt.x * qt.z;
		const flt32 yw = qt.w * qt.y;

		const flt32 yz = qt.y * qt.z;
		const flt32 xw = qt.w * qt.x;

		return
		{
			1 - 2 * (y2 + z2), 2 * (xy - zw), 2 * (xz + yw), 0.0f,
			2 * (xy + zw), 1 - 2 * (x2 + z2), 2 * (yz - xw), 0.0f,
			2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
#endif