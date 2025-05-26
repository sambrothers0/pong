//
// Created by samjb on 2/5/2025.
//

#include "paddle.h"
#include "logic.h"

Paddle::Paddle(double xpos, double ypos)
    : xpos(xpos), ypos(ypos) {}

void Paddle::moveDown(double const tickRate) {
    double distance = (tickRate * PADDLE_SPEED);

    // ensure the paddle does not move too far
    if (distance > 50) distance = 50;
    ypos += distance;

    // paddle cannot go off screen
    if (ypos + PADDLE_HEIGHT >= SCREEN_HEIGHT) ypos = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void Paddle::moveUp(double const tickRate) {
    double distance = (tickRate * PADDLE_SPEED);

    // ensure the paddle does not move too far
    if (distance > 50) distance = 50; 
    ypos -= distance;
    
    // paddle cannot go off screen
    if (ypos <= 0) ypos = 0;
}