#pragma once

#ifdef EZ_STEAM_EXPORT
#define EZ_STEAM_API __declspec(dllexport)
#else
#define EZ_STEAM_API __declspec(dllimport)
#endif

#include <memory>
#include <cstdint>
#include <numeric>

#pragma warning(disable: 4251)