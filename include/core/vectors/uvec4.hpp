/* 4 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "uvec2.hpp"
#include "uvec3.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(16) uvec4
{
    union
    {
        struct
        {
            uin32 x, y, z, w;
        };
        uin32 arr[4];
        __m128i_u g;
    };

    uvec4(const uvec4 &v);
    uvec4(const uin32 val = 0U);
    uvec4(const uin32 ux, const uin32 uy, const uin32 uz, const uin32 uw);
	uvec4(const uvec2& xy, const uvec2& zw);
	uvec4(const uin32 x, const uvec3& yzw);
	uvec4(const uvec3& xyz, const uin32 w);

    uvec4 operator+(const uvec4& other) const;
	uvec4& operator+=(const uvec4& other);
	uvec4 operator-() const;
	uvec4 operator-(const uvec4& other) const;
	uvec4& operator-=(const uvec4& other);
    uvec4 operator*(const uvec4& other) const;
	uvec4& operator*=(const uvec4& other);
	uvec4 operator*(const uin32 val) const;
	uvec4& operator*=(const uin32 val);
    uvec4 operator/(const uvec4& other) const;
	uvec4& operator/=(const uvec4& other);
	uvec4 operator/(const uin32 val) const;
	uvec4& operator/=(const uin32 val);

	uin32 Dot(const uvec4& other) const;
	uin32 Distance(const uvec4& other) const;

	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const uvec4& v)
    {
        os << "( X: " << v.x << "\tY: "<< v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";

        return os;
    }
	#endif
};

uin32 Dot(const uvec4& v1, const uvec4& v2);
uin32 Distance(const uvec4& v1, const uvec4& v2);

#ifdef ENMA_IMPLEMENTATION
uvec4::uvec4(const uvec4& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}

uvec4::uvec4(uin32 val) : x(val), y(val), z(val), w(val) {}

uvec4::uvec4(uin32 ux, uin32 uy, uin32 uz, uin32 uw) : x(ux), y(uy), z(uz), w(uw) {}

uvec4::uvec4(const uvec2& xy, const uvec2& zw)
{
    this->x = xy.x;
    this->y = xy.y;
    this->z = zw.x;
    this->w = zw.y;
}

uvec4::uvec4(const uin32 x, const uvec3& yzw)
{
    this->x = x;
    this->y = yzw.x;
    this->z = yzw.y;
    this->w = yzw.z;
}

uvec4::uvec4(const uvec3& xyz, const uin32 w)
{
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = w;
}

uvec4 uvec4::operator+(const uvec4& other) const
{
    return uvec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

uvec4& uvec4::operator+=(const uvec4& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;

    return *this;
}

uvec4 uvec4::operator-() const
{
	return uvec4(-x, -y, -z, -w);
}

uvec4 uvec4::operator-(const uvec4& other) const
{
    return uvec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

uvec4& uvec4::operator-=(const uvec4& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;

    return *this;
}

uvec4 uvec4::operator*(const uvec4& other) const
{
    return uvec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

uvec4& uvec4::operator*=(const uvec4& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;

    return *this;
}

uvec4 uvec4::operator*(const uin32 val) const
{
    return uvec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

uvec4& uvec4::operator*=(const uin32 val)
{
    this->x *= val;
    this->y *= val;
    this->z *= val;
    this->w *= val;

    return *this;
}

uvec4 uvec4::operator/(const uvec4& other) const
{
    return uvec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

uvec4& uvec4::operator/=(const uvec4& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;

    return *this;
}

uvec4 uvec4::operator/(const uin32 val) const
{

    return uvec4(this->x / val, this->y / val, this->z / val, this->w / val);
}

uvec4& uvec4::operator/=(const uin32 val)
{
    this->x /= val;
    this->y /= val;
    this->z /= val;
    this->w /= val;

    return *this;
}

uin32 uvec4::Dot(const uvec4& other) const
{
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

uin32 Dot(const uvec4& v1, const uvec4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Not Tested Yet - Maybe Removed
uin32 uvec4::Distance(const uvec4& other) const
{
	const float xt = this->x - other.x;
	const float yt = this->y - other.y;
	const float zt = this->z - other.z;
	const float wt = this->w - other.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

// Not Tested Yet - Maybe Removed
uin32 Distance(const uvec4& v1, const uvec4& v2)
{
	const float xt = v1.x - v2.x;
	const float yt = v1.y - v2.y;
	const float zt = v1.z - v2.z;
	const float wt = v1.w - v2.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}
#endif