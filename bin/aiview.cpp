//
// Created by samjb on 2/5/2025.
//

#include <random>
#include "aiview.h"
#include <iostream>

aiView::aiView() {}

void aiView::update(Ball &ball, Paddle &rightPaddle, double tickRate) {
    // ai will randomly fail to track the ball sometimes
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(1, 10000);
    int aiRNG = dist(gen);

    if (aiRNG < 9965) {
        // fail to track the ball
        return;
    }

    if (ball.getYpos() + 80 > rightPaddle.getYbottom()) {       
        rightPaddle.moveDown(tickRate);
    } else if (ball.getYpos() - 40 < rightPaddle.getYpos()) {
        rightPaddle.moveUp(tickRate);
    }
}
