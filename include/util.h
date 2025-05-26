#include <string.h>
#include <cstdlib>
#include <iostream>
#include <SDL.h>

#ifndef UTIL_H
#define UTIL_H

inline void pong_error(const std::string& msg) {
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}


#endif