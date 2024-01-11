/* 3 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "bvec2.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct bvec3
{
	union 
    {
        struct
        {
            bln8 x, y, z;
        };
		bln8 arr[3];
    };
	
	bvec3(const bvec3& v);
	bvec3(const bln8 val = 0.0f);
	bvec3(const bln8 fx, const bln8 fy, const bln8 fz = 0.0f);
	bvec3(const bln8* arr);
	bvec3(const bln8 x, const bvec2& yz);
	bvec3(const bvec2& xy, const bln8 z);

    bln8 operator==(const bvec3& other);
    bln8 operator!=(const bvec3& other);

	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const bvec3& v)
	{
		os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";

		return os;
	}
	#endif
};

#ifdef ENMA_IMPLEMENTATION
bvec3::bvec3(const bvec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

bvec3::bvec3(const bln8 val) : x(val), y(val), z(val) {}

bvec3::bvec3(const bln8 fx, const bln8 fy, const bln8 fz) : x(fx), y(fy), z(fz) {}

bvec3::bvec3(const bln8* arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
	this->arr[2] = arr[2];
}

bvec3::bvec3(const bln8 x, const bvec2& yz)
{
	this->x = x;
	this->y = yz.x;
	this->z = yz.y;
}

bvec3::bvec3(const bvec2& xy, const bln8 z)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

bln8 bvec3::operator==(const bvec3& other)
{
    return this->x == other.x & this->y == other.y & this->z == other.z;
}

bln8 bvec3::operator!=(const bvec3& other)
{
    return this->x != other.x & this->y != other.y & this->z != other.z;
}
#endif