/* 4 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "bvec2.hpp"
#include "bvec3.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct bvec4
{
    union
    {
        struct
        {
            bln8 x, y, z, w;
        };
        bln8 arr[4];
    };

	bvec4(const bvec4& v);
	bvec4(const bln8 val = false);
    bvec4(const bln8 bx, const bln8 by, const bln8 bz = false, const bln8 bw = false);
    bvec4(const bln8* arr);
	bvec4(const bvec2& xy, const bvec2& zw);
	bvec4(const bln8 x, const bvec3& yzw);
	bvec4(const bvec3& xyz, const bln8 w);

    bln8 operator==(const bvec4& other);
    bln8 operator!=(const bvec4& other);
	
	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const bvec4& v)
    {
        os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";

        return os;
    }
	#endif
};


#ifdef ENMA_IMPLEMENTATION
bvec4::bvec4(const bvec4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

bvec4::bvec4(const bln8 val) : x(val), y(val), z(val), w(val) {}

bvec4::bvec4(const bln8 bx, const bln8 by, const bln8 bz, const bln8 bw) : x(bx), y(by), z(bz), w(bw) {}

bvec4::bvec4(const bln8* arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
	this->arr[2] = arr[2];
	this->arr[3] = arr[3];
}


bvec4::bvec4(const bvec2& xy, const bvec2& zw)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = zw.x;
	this->w = zw.y;
}

bvec4::bvec4(const bln8 x, const bvec3& yzw)
{
    this->x = x;
	this->y = yzw.x;
	this->z = yzw.y;
	this->w = yzw.z;
}

bvec4::bvec4(const bvec3& xyz, const bln8 w)
{
    this->x = xyz.x;
	this->y = xyz.y;
	this->z = xyz.z;
	this->w = w;
}

bln8 bvec4::operator==(const bvec4& other)
{
    return this->x == other.x & this->y == other.y & this->z == other.z & this->w == other.w;
}

bln8 bvec4::operator!=(const bvec4& other)
{
    return this->x != other.x & this->y != other.y & this->z != other.z & this->w != other.w;
}
#endif