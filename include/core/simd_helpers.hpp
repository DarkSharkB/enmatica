#pragma once
#include "../base.hpp"
#include "../empch.hpp"

#ifdef USE_SIMD
inline __m128 set1(const flt32 val);

#ifdef ENMA_IMPLEMENTATION
inline __m128 set1(const flt32 val)
{
	return _mm_set_ps1(val);
}
#endif

#endif