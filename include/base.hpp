#pragma once

#ifdef USE_MEM_ALIGNED
#define ALIGN(x) alignas(x)
#else
#define ALIGN(x)
#endif