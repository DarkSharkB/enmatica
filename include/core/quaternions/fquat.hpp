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
#include "../../base.hpp"
#include "../../empch.hpp"
#include "../../trignometry.hpp"

struct ALIGN(16) fquat
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
	static fquat ToQuaternion(const vec3 &eulerAngles);
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

#ifdef ENMA_IMPL
	fquat::fquat(const fquat &qt)
	{
		*this = qt;
	}

	fquat::fquat(const flt32 val) : w(1.0f), x(val), y(val), z(val) {}

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
		const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

		return fquat::Conjugate(q) / mag;
	}
	
	fquat fquat::Rotate(flt32 angle, const vec3 &axis)
	{
		#if defined(USE_AUTO_DEG)
		const flt32 hang = ToRadians(angle) * 0.5f;
		#else
		const flt32 hang = angle * 0.5f;
		#endif
		const flt32 cosha = cos(hang);
		const flt32 sinha = sin(hang);

		return { cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z };
	}

	fquat fquat::ToQuaternion(const vec3 &eulerAngles)
	{
		#if defined(USE_AUTO_DEG)
		const vec3 heuler = ToRadians(eulerAngles) * 0.5f; 	// A little optimisation, not much
		#else
		const vec3 heuler = eulerAngles * 0.5f;
		#endif

		const flt32 cX = cos(heuler.x);
		const flt32 cY = cos(heuler.y);
		const flt32 cZ = cos(heuler.z);

		const flt32 sX = sin(heuler.x);
		const flt32 sY = sin(heuler.y);
		const flt32 sZ = sin(heuler.z);

		return
		{
			cY * cX * cZ + sY * sX * sZ,
			cY * sX * cZ + sY * cX * sZ,
			sY * cX * cZ - cY * sX * sZ,
			cY * cX * sZ - sY * sX * cZ
		};
	}

	vec3 fquat::ToEulerAngles(const fquat &qt)
	{
		flt32 heading, pitch, bank;
		const flt32 sX = -2.0f * (qt.y * qt.z - qt.w * qt.x);
		const flt32 hmX2 = 0.5f - qt.x * qt.x;

		const flt32 xzPwy = qt.x * qt.z + qt.w * qt.y;
		const flt32 y2 = qt.y * qt.y;
		const flt32 z2 = qt.z * qt.z;

		if (abs(sX) > 0.9999f)
		{
			pitch = HALF_PI * sX;
			heading = atan2(-xzPwy, 0.5f - y2 - z2);
			bank = 0.0f;
		}
		else
		{
			pitch = asin(sX);
			heading = atan2(xzPwy, hmX2 - y2);
			bank = atan2(qt.x * qt.y + qt.w * qt.z, hmX2 - z2);
		}

		return { pitch, heading, bank };
	}

	mat4x4 fquat::ToRotationMatrix(const fquat &qt)
	{
		const flt32 x2 = qt.x * qt.x;
		const flt32 y2 = qt.y * qt.y;
		const flt32 z2 = qt.z * qt.z;

		const flt32 xy = qt.x * qt.y;
		const flt32 wz = qt.w * qt.z;

		const flt32 xz = qt.x * qt.z;
		const flt32 wy = qt.w * qt.y;

		const flt32 yz = qt.y * qt.z;
		const flt32 wx = qt.w * qt.x;

		return
		{
			1 - 2 * (y2 + z2),	2 * (xy + wz), 		2 * (xz - wy), 		0.0f,
			2 * (xy - wz),		1 - 2 * (x2 + z2),	2 * (yz + wx), 		0.0f,
			2 * (xz + wy),		2 * (yz - wx), 		1 - 2 * (x2 + y2), 	0.0f,
			0.0f, 				0.0f, 				0.0f, 				1.0f
		};
	}
#endif