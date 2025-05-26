//
// Created by samjb on 2/5/2025.
//

#include <SDL_ttf.h>
#include "ball.h"
#include "paddle.h"

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

class Playerview {
public:
    Playerview();
    void update(Logic &logic);
    void shutdown() const;

    void drawBall(const Logic &logic) const;
    void drawPaddle(const int paddleId, const Logic &logic) const;

    void showStartupScreen();
    void showEndScreen(const int result);

    void drawScores(const Logic &logic) const ;

    SDL_Window* gameWindow;
    SDL_Window* startupWindow;
    SDL_Window* endWindow;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
    TTF_Font* font;
};

#endif //PLAYERVIEW_H
