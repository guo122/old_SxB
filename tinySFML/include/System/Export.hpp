
#ifndef TTSFML_SYSTEM_EXPORT_HPP
#define TTSFML_SYSTEM_EXPORT_HPP

#include "Config.hpp"

#if defined(tinySFML_System_EXPORTS)

#define TTSFML_SYSTEM_API TTSFML_API_EXPORT

#else

#define TTSFML_SYSTEM_API TTSFML_API_IMPORT

#endif

#endif // TTSFML_EXPORT_HPP