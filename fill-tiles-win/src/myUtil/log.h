//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_LOG_H
#define FILL_TILES_LOG_H

#include <stdafx.h>

#define DEBUG_BUILD

#define LOG_INFO std::cout << "\n[INFO] " << __FILE__  << " ** " << __FUNCTION__ << " ** " << __LINE__ << std::endl
#define LOG_CAUTION std::cout << "\n[CAUTION] " << __FILE__  << " ** " << __FUNCTION__ << " ** " << __LINE__ << std::endl
#define LOG_ERR std::cerr << "\n[ERR] " << __FILE__  << " ** " << __FUNCTION__ << " ** " << __LINE__ << std::endl

#define LOG_ASSERT(expr, log) assert((expr)&&(log))

#endif //FILL_TILES_LOG_H
