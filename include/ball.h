//
// Created by samjb on 2/5/2025.
//

#include "audio.h"

#ifndef BALL_H
#define BALL_H

const float BALL_RADIUS = 10;

class Ball {
public:
    Ball();

    //getters
    double getXpos() const { return xpos; }
    double getYpos() const { return ypos; }
    double getXvelo() const { return xvelo; }
    double getYvelo() const { return yvelo; }
    double getRadius() const { return BALL_RADIUS; }

    //setters
    void setXpos(double const x) { xpos = x; }
    void setYpos(double const y) { ypos = y; }
    void setXvelo(double const x) { xvelo = x; }
    void setYvelo(double const y) { yvelo = y; }

    void update(double const tickRate, Audio &audio);

private:
    double xpos, ypos, xvelo, yvelo;
    double speedScalar;
};

#endif //BALL_H
