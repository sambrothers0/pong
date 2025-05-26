//
// Created by samjb on 2/5/2025.
//

#include "ball.h"
#include "paddle.h"

#ifndef AIVIEW_H
#define AIVIEW_H

class aiView {
public:
    aiView();

    void update(Ball &ball, Paddle &rightPaddle, double tickRate);

private:

};

#endif //AIVIEW_H
