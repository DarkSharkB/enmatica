/* Double Precision Floating-Point Quaternions
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(32) dquat
{
	union
	{
		struct 
		{
			flt64 w;
			flt64 x;
			flt64 y;
			flt64 z;
		};
		flt64 arr[4];
	};

public:
	dquat(const dquat &qt);
	dquat(const flt64 val = 0.0f);
	dquat(const flt64 fw, const flt64 fx, const flt64 fy = 0.0f, const flt64 fz = 0.0f);
	dquat(const flt64 w, const vec3 xyz);
	
	dquat operator+(const dquat other);
	dquat operator+=(const dquat other);
	dquat operator-(const dquat other);
	dquat operator-=(const dquat other);
	dquat operator*(const dquat &other);
	dquat operator*(const flt64 val);
	dquat operator*=(const flt64 val);
	dquat operator/(const flt64 val);
	dquat operator/=(const flt64 val);

	static dquat Conjugate(const dquat &q);
	static dquat Normalise(dquat q);
	static dquat Inverse(const dquat &q);
	static dquat Rotate(flt64 angle, const vec3 &axis);
	static dquat ToQuaternion(vec3 rot);
	static vec3 ToEulerAngles(const dquat &qt);
	static mat4x4 ToRotationMatrix(const dquat &qt);

	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, dquat qt)
	{
		os << "( W: " << qt.w << "\tX: " << qt.x << "\tY: " << qt.y << "\tZ: " << qt.z << " )";

		return os;
	}
	#endif
};

#ifdef ENMA_IMPLEMENTATION
	dquat::dquat(const dquat &qt)
	{
		*this = qt;
	}

	dquat::dquat(const flt64 val) : x(val), y(val), z(val) {
		w = 1.0f;
	}

	dquat::dquat(const flt64 fw, const flt64 fx, const flt64 fy, const flt64 fz) : w(fw), x(fx), y(fy), z(fz) {}

	dquat::dquat(const flt64 w, const vec3 xyz)
	{
		this->w = w;
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
	}

	dquat dquat::operator+(const dquat other)
	{
		return { this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z };
	}

	dquat dquat::operator+=(const dquat other)
	{
		this->w += other.w;
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	dquat dquat::operator-(const dquat other)
	{
		return { this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z };
	}

	dquat dquat::operator-=(const dquat other)
	{
		this->w -= other.w;
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	dquat dquat::operator*(const dquat &other)
	{
		return 
		{
			this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
			this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
			this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
			this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
		};
	}

	dquat dquat::operator*(const flt64 val)
	{
		return { w * val, x * val, y * val, z * val };
	}

	dquat dquat::operator*=(const flt64 val)
	{
		this->w *= val;
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return *this;
	}

	dquat dquat::operator/(const flt64 val)
	{
		const flt64 div = 1.0f / val;

		return { w * div, x * div, y * div, z * div };
	}

	dquat dquat::operator/=(const flt64 val)
	{
		const flt64 div = 1.0f / val;

		this->w *= div;
		this->x *= div;
		this->y *= div;
		this->z *= div;

		return *this;
	}

	dquat dquat::Conjugate(const dquat &q)
	{
		return { q.w, -q.x, -q.y, -q.z };
	}

	dquat dquat::Normalise(dquat q)
	{
		const flt64 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

		return q / mag;
	}

	dquat dquat::Inverse(const dquat &q)
	{
		const flt64 mag2 = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;

		return dquat::Conjugate(q) / mag2;
	}
	
	/*dquat dquat::Rotate(flt64 angle, const vec3 &axis)
	{
		const flt64 hang = angle * 0.5f;
		const flt64 cosha = cos(hang);
		const flt64 sinha = sin(hang);

		return { cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z };
	}

	dquat dquat::ToQuaternion(vec3 eulerAngles)
	{
		const vec3 heuler = eulerAngles * 0.5f;	// A little SIMD optimisation, not much

		const flt64 cr = cos(heuler.x);
		const flt64 cp = cos(heuler.y);
		const flt64 cy = cos(heuler.z);

		const flt64 sr = sin(heuler.x);
		const flt64 sp = sin(heuler.y);
		const flt64 sy = sin(heuler.z);

		return
		{
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		};
	}

	vec3 dquat::ToEulerAngles(const dquat &qt)
	{
		const flt64 y2 = qt.y * qt.y;
		const flt64 wysxz2 = 2 * (qt.w * qt.y - qt.x * qt.z);

		// X-axis Rotation
		const flt64 sinr_cosp = 2 * (qt.w * qt.x + qt.y * qt.z);
		const flt64 cosr_cosp = 1 - 2 * (qt.x * qt.x + y2);
		const flt64 r = std::atan2(sinr_cosp, cosr_cosp);

		// Y-axis Rotation
		flt64 sinp = std::sqrt(1 + wysxz2);
		flt64 cosp = std::sqrt(1 - wysxz2);
		flt64 p = 2 * std::atan2(sinp, cosp) - pi / 2;	// Original

		const flt64 p = std::asin(wysxz2);	// Alternative - hope it's same

		// Z-axis Rotation
		const flt64 siny_cosp = 2 * (qt.w * qt.z + qt.x * qt.y);
		const flt64 cosy_cosp = 1 - 2 * (y2 + qt.z * qt.z);
		const flt64 y = std::atan2(siny_cosp, cosy_cosp);

		return { r, p, y };
	}

	mat4x4 dquat::ToRotationMatrix(const dquat &qt)
	{
		const flt64 x2 = qt.x * qt.x;
		const flt64 y2 = qt.y * qt.y;
		const flt64 z2 = qt.z * qt.z;

		const flt64 xy = qt.x * qt.y;
		const flt64 zw = qt.w * qt.z;

		const flt64 xz = qt.x * qt.z;
		const flt64 yw = qt.w * qt.y;

		const flt64 yz = qt.y * qt.z;
		const flt64 xw = qt.w * qt.x;

		return
		{
			1 - 2 * (y2 + z2), 2 * (xy - zw), 2 * (xz + yw), 0.0f,
			2 * (xy + zw), 1 - 2 * (x2 + z2), 2 * (yz - xw), 0.0f,
			2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}*/
#endif