#define ENMATICA_IMPL
#include "enma.hpp"

// For testing purposes only. Do not use this in your project
std::ostream &operator<<(std::ostream &os, const __m128 vec)
{
    os << "| X: " << vec[0] << "\tY: " << vec[1] << "\tZ: " << vec[2] << "\tW: " << vec[3] << " |";

    return os;
}


std::ostream &operator<<(std::ostream &os, const __m256 vec)
{
    os << "| X1: " << vec[0] << "\tY1: " << vec[1] << "\tZ1: " << vec[2] << "\tW1: " << vec[3] << " |"
    <<    "| X2: " << vec[4] << "\tY2: " << vec[5] << "\tZ2: " << vec[6] << "\tW2: " << vec[7] << " |";

    return os;
}