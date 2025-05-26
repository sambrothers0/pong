//
// Created by samjb on 2/5/2025.
//
#include <random>
#include <SDL.h>
#include "logic.h"
#include "ball.h"
#include "paddle.h"

Logic::Logic() 
    : playerScore(0), 
    aiScore(0), 
    ball(), 
    leftPaddle(0.0, SCREEN_HEIGHT/2), 
    rightPaddle(1010.0, SCREEN_HEIGHT/2),
    gameWindowOn(true),
    gameActive(true), 
    aiInstance(),
    audio() {}

void Logic::update(bool &running, double tickRate) {
    // dont begin game until startup window has closed
    if (startupWindowOn) {
        return;
    }

    // check if window has been closed
    if (!gameWindowOn) {
        running = false;
        return;
    }

    // check for game end
    if (endWindowOn) {
        aiScore = 0;
        playerScore = 0;

        // determine a new difficulty for the ai
        std::random_device rd;
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<int> dist(10000, 100000);
        aiDifficulty = dist(gen);
        return;
    }
    
    // check for paddle hit
    // left paddle
    if (ball.getXpos() < leftPaddle.getXright() && ball.getYpos() > leftPaddle.getYpos() && ball.getYpos() < leftPaddle.getYbottom()) {
        // slight random perturbation when ball hits paddle
        std::random_device rd;
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<double> dist(-0.05, 0.05);

        ball.setXvelo(-ball.getXvelo() + dist(gen));
        ball.setYvelo(ball.getYvelo() + dist(gen));

        ball.setXpos(ball.getXpos() + 1);

        // load and play audio
        audio.loadSound("paddle_hit", "../resource/paddle_hit.wav");
        audio.playSound("paddle_hit");
    // right paddle
    } else if (ball.getXpos() > rightPaddle.getXpos() && ball.getYpos() > rightPaddle.getYpos() && ball.getYpos() < rightPaddle.getYbottom()) {
        // slight random perturbation when ball hits paddle
        std::random_device rd;
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<double> dist(-0.05, 0.05);

        ball.setXvelo(-ball.getXvelo() + dist(gen));
        ball.setYvelo(ball.getYvelo() + dist(gen));

        ball.setXpos(ball.getXpos() - 1);

        // load and play audio
        audio.loadSound("paddle_hit", "../resource/paddle_hit.wav");
        audio.playSound("paddle_hit");
    }

    // check for round end
    if (ball.getXpos() < 0) {
        aiScore++;
        ball = Ball();
        audio.loadSound("round_lose", "../resource/round_lose.wav");
        audio.playSound("round_lose");
        
        SDL_Delay(1000);
        return;
    } else if (ball.getXpos() > SCREEN_WIDTH) {
        playerScore++;
        ball = Ball();
        audio.loadSound("round_win", "../resource/round_win.wav");
        audio.playSound("round_win");

        SDL_Delay(1000);
        return;
    }

    // determine AI behavior
    aiInstance.update(ball, rightPaddle, tickRate);

    this->tickRate = tickRate;
    ball.update(tickRate, audio);
}

void Logic::leftPaddleUp() {
    leftPaddle.moveUp(tickRate);
}

void Logic::leftPaddleDown() {
    leftPaddle.moveDown(tickRate);
}

void Logic::rightPaddleDown() {
    rightPaddle.moveDown(tickRate);
}

void Logic::rightPaddleUp() {
    rightPaddle.moveUp(tickRate);
}
