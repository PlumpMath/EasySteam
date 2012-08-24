#pragma once

#define STEAMWORKS_CLIENT_INTERFACES

#ifdef EZ_STEAM_EXPORT
#define EZ_STEAM_API __declspec(dllexport)
#else
#define EZ_STEAM_API __declspec(dllimport)
#endif

#include <memory>
#include <cstdint>
#include <numeric>

#include <boost/signals.hpp>

#pragma warning(disable: 4251)