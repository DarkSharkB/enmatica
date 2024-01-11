/* 2 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../../base.hpp"
#include "../../empch.hpp"

struct bvec2
{
    union 
    {
        struct
        {
            bln8 x, y;
        };
        bln8 arr[2];
    };

	bvec2(const bvec2& vec);
	bvec2(const bln8 val = false);
    bvec2(const bln8 bx, const bln8 by);
	bvec2(const bln8* arr);

    bln8 operator==(const bvec2& other);
    bln8 operator!=(const bvec2& other);

    bvec2 Equals(const bvec2& other);
	
	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const bvec2& vec)
    {
        os << "( X: " << vec.x << "\tY: " << vec.y << " )";

        return os;
    }
	#endif
};

#ifdef ENMA_IMPLEMENTATION
bvec2::bvec2(const bvec2& v)
{
    this->x = v.x;
    this->y = v.y;
}

bvec2::bvec2(const bln8 val) : x(val), y(val) {}

bvec2::bvec2(const bln8 bx, const bln8 by) : x(bx), y(by) {}

bvec2::bvec2(const bln8* arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
}

bln8 bvec2::operator==(const bvec2& other)
{
    return this->x == other.x & this->y == other.y;
}

bln8 bvec2::operator!=(const bvec2& other)
{
    return this->x != other.x & this->y != other.y;
}

bvec2 bvec2::Equals(const bvec2& other)
{
    return bvec2(this->x == other.x, this->y == other.y);
}
#endif