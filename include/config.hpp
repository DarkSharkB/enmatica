/** Define all the required features here; available features listed below
*   USE_SIMD_SPEC       -   Use to invoke functions that uses SIMD intrinsics whenever possible
*   USE_MEM_ALIGNED     -   Use to align datatypes to memory properly; 
                            Note - Can improve processing speed but leads to wastage of space and not recommended if target device has low bandwidth
*   USE_ONLY_RAD        -   Use radians in functions in which angle is a parameter; Used by Default
*   USE_AUTO_DEG        -   Use degrees in functions in which angle is a parameter
*   USE_LH_YU           -   Use to invoke projection functions with Left-Handed Y-up Cartesian Coordinates; Used by Default
*/
#define USE_SIMD_SPEC
#define USE_MEM_ALIGNED
#define USE_AUTO_DEG