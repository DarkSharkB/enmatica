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
 *  Do not define any of the macros present down here! 
 *
 *   USE_SIMD            -  Use to invoke functions that uses SIMD intrinsics whenever possible
 *   USE_SIMD_ALIGNED     -  Use to align data types to memory properly; Use along with USE_SIMD. Not alone
 *                          Note - Can improve processing speed but leads to wastage of space and not recommended if target device has low bandwidth
 *   USE_RAD             -  Use radians in functions in which angle is a parameter; Used by Default
 *   USE_DEG             -  Use degrees in functions in which angle is a parameter
 *   USE_LH_YU           -  Use to invoke projection functions that uses Left-Handed Y-up Cartesian Coordinates; Used by Default; 
 *                          Note - Support for other Coordinates yet to be planned
 *   ENMA_ENABLE_NS      - Enables namespace Enmatica in the project; Useful to avoid name conflicts
 */

/**
 * Configuration Starts Here
 */

#define USE_SIMD
#define USE_SIMD_ALIGNED
#define USE_SIMD_UNALIGNED
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