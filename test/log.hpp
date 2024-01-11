#pragma once

#ifdef DEBUG
#include <iostream>

#define LOG_D(stm)                                                                  \
    std::cout << "DEBUG: " << stm << '\n'                                           \

#define LOG_W(stm)                                                                  \
    std::cout << "WARN [" << __FILE__ << ": " << __LINE__ << "]: " << stm << '\n'   \

#define LOG_E(stm)                                                                  \
    std::cout << "ERROR [" << __FILE__ << ": " << __LINE__ << "]: " << stm << '\n'  \

#endif

#ifndef DEBUG

#define LOG_D(_ig)

#define LOG_W(_ig)

#define LOG_E(_ig)

#endif