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
			flt32 w, x, y, z;
		};
		flt32 arr[4];
	};

public:
	fquat(const fquat& q);
	fquat(const flt32 val = 0.0f);
	fquat(const flt32 fw, const flt32 fx, const flt32 fy = 0.0f, const flt32 fz = 0.0f);
	fquat(const flt32 w, const vec3& xyz);
	
	fquat operator+(const fquat& other) const;
	fquat& operator+=(const fquat& other);
	fquat operator-() const;
	fquat operator-(const fquat& other) const;
	fquat& operator-=(const fquat& other);
	fquat operator*(const fquat& other) const;
	fquat operator*(const flt32 val) const;
	fquat& operator*=(const flt32 val);
	fquat operator/(const flt32 val) const;
	fquat& operator/=(const flt32 val);

	flt32 Dot(const fquat& other) const;
	fquat Conjugate() const;
	fquat Normalise() const;
	fquat Inverse() const;

	vec3 ToEulerAngles() const;
	mat4x4 ToRotationMatrix() const;

	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const fquat& q)
	{
		os << "( W: " << q.w << "\tX: " << q.x << "\tY: " << q.y << "\tZ: " << q.z << " )";

		return os;
	}
	#endif
};

flt32 Dot(const fquat& q1, const fquat& q2);
fquat Conjugate(const fquat& q);
fquat Normalise(const fquat& q);
fquat Inverse(const fquat& q);
//fquat Rotate(const flt32 angle, const vec3& axis);

vec3 ToEulerAngles(const fquat& q);
mat4x4 ToRotationMatrix(const fquat& q);
fquat ToQuaternion(const vec3& eulerAngles);

#ifdef ENMA_IMPLEMENTATION
fquat::fquat(const fquat& q)
{
	this->w = q.w;
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
}

fquat::fquat(const flt32 val) : w(1.0f), x(val), y(val), z(val) {}

fquat::fquat(const flt32 fw, const flt32 fx, const flt32 fy, const flt32 fz) : w(fw), x(fx), y(fy), z(fz) {}

fquat::fquat(const flt32 w, const vec3& xyz)
{
	this->w = w;
	this->x = xyz.x;
	this->y = xyz.y;
	this->z = xyz.z;
}

fquat fquat::operator+(const fquat& other) const
{
	return { this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z };
}

fquat& fquat::operator+=(const fquat& other)
{
	this->w += other.w;
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

fquat fquat::operator-() const
{
	return { -this->w, -this->x, -this->y, -this->z };
}

fquat fquat::operator-(const fquat& other) const
{
	return { this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z };
}

fquat& fquat::operator-=(const fquat& other)
{
	this->w -= other.w;
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

fquat fquat::operator*(const fquat& other) const
{
	return 
	{
		this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
		this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
		this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
		this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
	};
}

fquat fquat::operator*(const flt32 val) const
{
	return { w * val, x * val, y * val, z * val };
}

fquat& fquat::operator*=(const flt32 val)
{
	this->w *= val;
	this->x *= val;
	this->y *= val;
	this->z *= val;

	return *this;
}

fquat fquat::operator/(const flt32 val) const
{
	const flt32 div = 1.0f / val;

	return { w * div, x * div, y * div, z * div };
}

fquat& fquat::operator/=(const flt32 val)
{
	const flt32 div = 1.0f / val;

	this->w *= div;
	this->x *= div;
	this->y *= div;
	this->z *= div;

	return *this;
}

flt32 fquat::Dot(const fquat& other) const
{
	return this->w * other.w + this->x * other.x + this->y * other.y + this->z * other.z;
}

flt32 Dot(const fquat& q1, const fquat& q2)
{
	return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

fquat fquat::Conjugate() const
{
	return fquat(this->w, -this->x, -this->y, -this->z);
}

fquat Conjugate(const fquat& q)
{
	return fquat(q.w, -q.x, -q.y, -q.z);
}

fquat fquat::Normalise() const
{
	const flt32 mag = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

	return *this / mag;
}

fquat Normalise(const fquat& q)
{
	const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

	return q / mag;
}

fquat fquat::Inverse() const
{
	const flt32 mag = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

	return Conjugate() / mag;
}

fquat Inverse(const fquat& q)
{
	const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

	return Conjugate(q) / mag;
}

/*fquat Rotate(const flt32 angle, const vec3& axis)
{
	#ifdef USE_AUTO_DEG
	const flt32 hang = ToRadians(angle) * 0.5f;
	#else
	const flt32 hang = angle * 0.5f;
	#endif
	const flt32 cosha = cos(hang);
	const flt32 sinha = sin(hang);

	return fquat(cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z);
}*/

fquat ToQuaternion(const vec3& eulerAngles)
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

vec3 fquat::ToEulerAngles() const
{
	flt32 heading, pitch, bank;
	const flt32 sX = -2.0f * (this->y * this->z - this->w * this->x);
	const flt32 hmX2 = 0.5f - this->x * this->x;

	const flt32 xzPwy = this->x * this->z + this->w * this->y;
	const flt32 y2 = this->y * this->y;
	const flt32 z2 = this->z * this->z;

	if(abs(sX) > 0.9999f)
	{
		pitch = HALF_PI * sX;
		heading = atan2(-xzPwy, 0.5f - y2 - z2);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sX);
		heading = atan2(xzPwy, hmX2 - y2);
		bank = atan2(this->x * this->y + this->w * this->z, hmX2 - z2);
	}

	return vec3(pitch, heading, bank);
}

vec3 ToEulerAngles(const fquat& q)
{
	flt32 heading, pitch, bank;
	const flt32 sX = -2.0f * (q.y * q.z - q.w * q.x);
	const flt32 hmX2 = 0.5f - q.x * q.x;

	const flt32 xzPwy = q.x * q.z + q.w * q.y;
	const flt32 y2 = q.y * q.y;
	const flt32 z2 = q.z * q.z;

	if(abs(sX) > 0.9999f)
	{
		pitch = HALF_PI * sX;
		heading = atan2(-xzPwy, 0.5f - y2 - z2);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sX);
		heading = atan2(xzPwy, hmX2 - y2);
		bank = atan2(q.x * q.y + q.w * q.z, hmX2 - z2);
	}

	return { pitch, heading, bank };
}

mat4x4 fquat::ToRotationMatrix() const
{
	const flt32 x2 = this->x * this->x;
	const flt32 y2 = this->y * this->y;
	const flt32 z2 = this->z * this->z;

	const flt32 xy = this->x * this->y;
	const flt32 wz = this->w * this->z;

	const flt32 xz = this->x * this->z;
	const flt32 wy = this->w * this->y;

	const flt32 yz = this->y * this->z;
	const flt32 wx = this->w * this->x;

	return
	{
		1 - 2 * (y2 + z2),	2 * (xy + wz), 		2 * (xz - wy), 		0.0f,
		2 * (xy - wz),		1 - 2 * (x2 + z2),	2 * (yz + wx), 		0.0f,
		2 * (xz + wy),		2 * (yz - wx), 		1 - 2 * (x2 + y2), 	0.0f,
		0.0f, 				0.0f, 				0.0f, 				1.0f
	};
}

mat4x4 ToRotationMatrix(const fquat& q)
{
	const flt32 x2 = q.x * q.x;
	const flt32 y2 = q.y * q.y;
	const flt32 z2 = q.z * q.z;

	const flt32 xy = q.x * q.y;
	const flt32 wz = q.w * q.z;

	const flt32 xz = q.x * q.z;
	const flt32 wy = q.w * q.y;

	const flt32 yz = q.y * q.z;
	const flt32 wx = q.w * q.x;

	return
	{
		1 - 2 * (y2 + z2),	2 * (xy + wz), 		2 * (xz - wy), 		0.0f,
		2 * (xy - wz),		1 - 2 * (x2 + z2),	2 * (yz + wx), 		0.0f,
		2 * (xz + wy),		2 * (yz - wx), 		1 - 2 * (x2 + y2), 	0.0f,
		0.0f, 				0.0f, 				0.0f, 				1.0f
	};
}
#endif