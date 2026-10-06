/**
 * Project Configuration
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_CONFIG_HPP
#define ENMA_CONFIG_HPP

/** 
 * All available compile-time tunable features are described below
 *
 *  Do not pass any of the macros present down as compiler flag if configured here! 
 *
 *   USE_SIMD         -  Use to invoke functions that uses SIMD intrinsics whenever possible
 *   USE_SIMD_ALIGNED -  Use to align data types with memory properly; Ignored if USE_SIMD is not used
 *                       Note: Improves processing speed but increases memory usage
                             Not recommended if target device has low bandwidth
 *   USE_RAD          -  Allow angles to be passed in radians in functions with angle as parameter; Used by Default
 *   USE_DEG          -  Allow angles to be passed in degrees in functions with angle as parameter
 *   USE_LH_YU        -  Use to invoke projection functions that uses Left-Handed Y-up Cartesian Coordinates; Used by Default
 *                       Note: Support for other Coordinates Systems are yet to be planned
 *   ENMA_ENABLE_NS   -  Enables namespace Enmatica in the project; Useful to avoid name conflicts
 */

/**
 * Configuration Starts Here
 */

#define USE_SIMD
#define USE_SIMD_ALIGNED
#define USE_DEG
#define USE_LH_YU

/**
 * Configuration Ends Here
 */

#ifdef USE_SIMD
  #ifndef USE_SIMD_ALIGNED
  #define USE_SIMD_UNALIGNED
  #endif  // USE_SIMD_ALIGNED
#endif // USE_SIMD

#ifdef USE_DEG
  #undef USE_RAD
#endif // USE_DEG

#ifdef ENMA_ENABLE_NS
namespace Enmatica{};
namespace enma = Enmatica;
#endif // ENMA_ENABLE_NS

#endif // ENMA_CONFIG_HPP