//
// Created by samjb on 2/5/2025.
//

#ifndef PADDLE_H
#define PADDLE_H

const double PADDLE_WIDTH = 14.0;
const double PADDLE_HEIGHT = 200.0;
const double PADDLE_SPEED = 50.0;

class Paddle {
public:
    Paddle(double const xpos, double const ypos);

    //getters
    double getXpos() const { return xpos; }
    double getYpos() const { return ypos; }
    double getHeight() const { return PADDLE_HEIGHT; }
    double getWidth() const { return PADDLE_WIDTH; }
    double getYbottom() const { return ypos + PADDLE_HEIGHT; }
    double getXright() const { return xpos + PADDLE_WIDTH; }

    void moveDown(double const tickRate);
    void moveUp(double const tickRate);

private:
    double xpos, ypos;
};

#endif //PADDLE_H
