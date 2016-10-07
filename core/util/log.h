#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <ctime>

#define LOG_LEVEL 2

#if LOG_LEVEL >= 3
#define DEBUG(x) std::cout << "[DEBUG]" << x << std::endl;
#else
#define DEBUG(x)
#endif

#if LOG_LEVEL >= 2
#define INFO(x) std::cout << "[INFO]" << x << std::endl;
#else
#define INFO(x)
#endif

#if LOG_LEVEL >= 1
#define WARNING(x) std::cout << "[WARNING]" << x << std::endl;
#else
#define WARNING(x)
#endif

#if LOG_LEVEL >= 0
#define ERR(x) std::cout << "[ERROR]" << x << std::endl;
#else
#define ERR(x)
#endif

#endif // !LOG_H
