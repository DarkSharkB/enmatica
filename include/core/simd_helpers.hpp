/** 
 * \brief Helper functions for SIMD operations
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SIMD_HELPERS_HPP
#define ENMA_SIMD_HELPERS_HPP

#include <intrin.h>
#include "config.hpp"
#include "base.hpp"
#include "types.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

#ifdef USE_SIMD
/**
 * \brief Helper function to fill a `__m128` vector
 *        with a single `flt32` input value
 * 
 * \param val Value to fill the vector
 * \return __m128 The output vector filled 
 *				        with the input value
 */
inline __m128 Set1(flt32 val);
#endif // USE_SIMD

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef USE_SIMD
inline __m128 Set1(flt32 val)
{
	return _mm_set_ps1(val);
}
#endif // USE_SIMD

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SIMD_HELPERS_HPP