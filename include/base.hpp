#pragma once

#ifndef ENMA_BASE_HPP
#define ENMA_BASE_HPP

#ifdef USE_SIMD_ALIGNED
#define ALIGN(x) alignas(x)
#else
#define ALIGN(x)
#endif

#ifdef ENMA_ENABLE_NS
#define ENMA_NS_START     \
namespace enmatica        \
{                               

#define ENMA_NS_END       \
} // namespace enmatica
#else // !ENMA_ENABLE_NS
#define ENMA_NS_START
#define ENMA_NS_END
#endif // ENMA_ENABLE_NS && !ENMA_ENABLE_NS

#endif // ENMA_BASE_HPP