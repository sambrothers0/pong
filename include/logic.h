//
// Created by samjb on 2/5/2025.
//

#include "audio.h"
#include "ball.h"
#include "paddle.h"
#include "aiview.h"

#ifndef LOGIC_H
#define LOGIC_H

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

class Logic {
public:
    Logic();
    void update(bool &running, double tickRate);
    
    // paddle movers
    void leftPaddleUp();
    void leftPaddleDown();
    void rightPaddleUp();
    void rightPaddleDown();  

    // getters
    Ball getBall() const { return ball; };
    Paddle getLeftPaddle() const { return leftPaddle; };
    Paddle getRightPaddle() const { return rightPaddle; };

    int getGamesPlayed() const { return gamesPlayed; }
    int getPlayerScore() const { return playerScore; }
    int getAIScore() const { return aiScore; }

    bool getGameWindowOn() const { return gameWindowOn; }
    bool getStartupWindowOn() const { return startupWindowOn; }
    bool getEndWindowOn() const { return endWindowOn; }

    double getTickRate() const { return tickRate; }
    bool getGameActive() const { return gameActive; }

    // setters
    void setGameWindowOn(bool newVal) { gameWindowOn = newVal; }
    void setStartupWindowOn(bool newVal) { startupWindowOn = newVal; }
    void setEndWindowOn(bool newVal) { endWindowOn = newVal; }

private:
    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;

    unsigned int gamesPlayed;
    unsigned int playerScore;
    unsigned int aiScore;

    bool gameWindowOn;
    bool startupWindowOn;
    bool endWindowOn;

    double tickRate;
    bool gameActive;

    aiView aiInstance;
    int aiDifficulty;

    Audio audio;
};

#endif //LOGIC_H
