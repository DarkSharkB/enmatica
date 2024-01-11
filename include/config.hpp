/** Define all the required features here; available features listed below
 *
 *   USE_SIMD            -  Use to invoke functions that uses SIMD intrinsics whenever possible
 *   USE_MEM_ALIGNED     -  Use to align data types to memory properly; Use along with USE_SIMD. Not alone
 *                          Note - Can improve processing speed but leads to wastage of space and not recommended if target device has low bandwidth
 *   USE_RAD             -  Use radians in functions in which angle is a parameter; Used by Default
 *   USE_DEG             -  Use degrees in functions in which angle is a parameter
 *   USE_LH_YU           -  Use to invoke projection functions that uses Left-Handed Y-up Cartesian Coordinates; Used by Default; 
 *                          Note - Support for other Coordinates yet to be planned
 */

/**
 * Configuration Starts Here
 */

#define USE_SIMD
//#define USE_MEM_ALIGNED
#define USE_DEG
#define USE_LH_YU

/**
 * Configuration Ends Here
 */

#ifdef USE_MEM_ALIGNED
    #ifndef USE_SIMD
    #define USE_SIMD
    #endif
#endif

#ifdef USE_DEG
    #undef USE_RAD
#elif USE_RAD
    #undef USE_DEG
#endif
