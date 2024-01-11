/* Single Precision Floating-Point 3x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../../vector.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct fmat3x4
{
    union
    {
        struct
        {
            flt32 m11, m12, m13, m14;
            flt32 m21, m22, m23, m24;
            flt32 m31, m32, m33, m34;
        };
    };
};

#ifdef ENMA_IMPLEMENTATION

#endif