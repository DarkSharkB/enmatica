/**
 * @author DarkShark
 * @brief The Pre-Compiled Header file of the Enmatica library. Well, I actually didn't used it as intended anyway :)
 * 
 * @copyright Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once

#ifdef DEBUG
    #include <iostream>
    #include <iomanip>
#endif
    
#include <cmath> 
#include <algorithm>
#include <string>
#include <ctime>

// Intrinsic Functions
#include <intrin.h>

/*#ifdef DEBUG
void print128(const __m128 vec)
{
    std::cout << "X: " << vec[0] << "\tY: " << vec[1] << "\tZ: " << vec[2] << "\tW: " << vec[3] << std::endl;
}

void print256(const __m256 vec)
{
    std::cout << "X1: " << vec[0] << "\tY1: " << vec[1] << "\tZ1: " << vec[2] << "\tW1: " << vec[3] << std::endl;
    std::cout << "X2: " << vec[4] << "\tY2: " << vec[5] << "\tZ2: " << vec[6] << "\tW2: " << vec[7] << std::endl;
}
#endif*/

#include "types.hpp"

#define ALIGN(x) alignas(x)