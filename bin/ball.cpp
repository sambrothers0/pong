//
// Created by samjb on 2/5/2025.
//
#include <random>
#include <stdio.h>
#include <iostream>
#include "ball.h"
#include "logic.h"

Ball::Ball() : xpos(SCREEN_WIDTH/2), ypos(SCREEN_HEIGHT/2), speedScalar(0.5) {
    // this code ensures the ball is given a random velocity 
    // in a random xy direction, such that the x and y velocities
    // have an aboslute value totaling to 1

    // generating random number for starting ball velocity
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<double> dist(0.42, 1);

    // total velocity in x and y equals 1, minimum 0.42 for x
    // so it doesnt bounce vertically forever
    double randomx = dist(gen);
    double randomy = 1 - randomx;

    // 50/50 chance to go in the opposite direction for x or y
    std::bernoulli_distribution boolDist(0.5);
    if (boolDist(gen)) {
        randomx = -randomx;
    }
    if (boolDist(gen)) {
        randomy = -randomy;
    }
    
    xvelo = randomx * speedScalar;
    yvelo = randomy * speedScalar;
}

void Ball::update(double const tickRate, Audio &audio)   {

    double newXpos = xpos + (xvelo * tickRate);
    double newYpos = ypos + (yvelo * tickRate);

    if (newYpos < 0) {
        // add a random perturbation to the balls reflection angle
        // by slightly changing its x and y velocity
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<double> dist(-0.05, 0.05);

        double deltaXvelo = dist(gen);
        double deltaYvelo = -deltaXvelo;

        xvelo += deltaXvelo;
        yvelo += deltaYvelo;
        
        newYpos = 0;
        yvelo = -yvelo;

        // load and play audio
        audio.loadSound("wall_hit", "../resource/wall_hit.wav");
        audio.playSound("wall_hit");
        return;
    }
    if (newYpos > SCREEN_HEIGHT) {
        // add a random perturbation to the balls reflection angle
        // by slightly changing its x and y velocity
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<double> dist(-0.05, 0.05);

        double deltaXvelo = dist(gen);
        double deltaYvelo = -deltaXvelo;

        xvelo += deltaXvelo;
        yvelo += deltaYvelo;
        
        newYpos = SCREEN_HEIGHT;
        yvelo = -yvelo;

        // load and play audio
        audio.loadSound("wall_hit", "../resource/wall_hit.wav");
        audio.playSound("wall_hit");
        return;
    }
    xpos = newXpos;
    ypos = newYpos;
}
