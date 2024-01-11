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
    #define CONSOLE_LOG
#endif
    
#include <cmath> 
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>

// For Hardware Intrinsics
#include <intrin.h>

#include "types.hpp"
#include "log.hpp"