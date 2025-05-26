//
// Created by samjb on 2/5/2025.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include "logic.h"
#include "playerview.h"
#include "util.h"

// defining color values to be used throughout the rendering
const unsigned char BACKGROUND_R = 16;
const unsigned char BACKGROUND_G = 18;
const unsigned char BACKGROUND_B = 28;
const unsigned char BALL_R = 83;
const unsigned char BALL_G = 102;
const unsigned char BALL_B = 221;
const unsigned char PADDLE_R = 83;
const unsigned char PADDLE_G = 102;
const unsigned char PADDLE_B = 221;
const unsigned char SCORE_R = 83;
const unsigned char SCORE_G = 102;
const unsigned char SCORE_B = 221;

Playerview::Playerview() {
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) pong_error("SDL could not initialize!");

    // Create window
    gameWindow= SDL_CreateWindow( "Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gameWindow == NULL ) pong_error("Window could not be created!");

    // init TTF
    if( TTF_Init() < 0 ) pong_error("Unable to initialize TTF!");

    // Load font
    font = TTF_OpenFont("../resource/Arial.ttf", 50);
    if (font == NULL) pong_error("Unable to open font!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // get renderer
    renderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL) pong_error("Unable to create renderer!");

    showStartupScreen();
}

void Playerview::update(Logic &logic) {
    // check if someone has won
    if (logic.getAIScore() >= 11) {
        logic.setEndWindowOn(true);
        showEndScreen(0);
    } else if (logic.getPlayerScore() >= 11) {
        logic.setEndWindowOn(true);
        showEndScreen(1);
    }

    bool windowFocus = true;

    // Event handler
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {

        // check for window close
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
            SDL_Window* closed_window = SDL_GetWindowFromID(e.window.windowID);
            if (closed_window == gameWindow) {
                logic.setGameWindowOn(false);

            } else if (closed_window == startupWindow) {
                logic.setStartupWindowOn(false);
                SDL_DestroyWindow(startupWindow);

            } else if (closed_window == endWindow) {
                logic.setEndWindowOn(false);
                SDL_DestroyWindow(endWindow);

            }
        }

        // only handle player input if window is in focus
        if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) windowFocus = true;
        if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST) windowFocus = false;

        // check for player input
        if (windowFocus) {
            if(e.type == SDL_KEYDOWN) {
                double tickRate = logic.getTickRate();
                if(e.key.keysym.sym == SDLK_q) logic.setGameWindowOn(false);
                if( e.key.keysym.sym == SDLK_UP ) logic.leftPaddleUp();
                if( e.key.keysym.sym == SDLK_DOWN ) logic.leftPaddleDown();

                // handle escape presses to close popup windows
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    if (logic.getStartupWindowOn()) {
                        logic.setStartupWindowOn(false);
                        SDL_DestroyWindow(startupWindow);
                    } else if (logic.getEndWindowOn()) {
                        logic.setEndWindowOn(false);
                        SDL_DestroyWindow(endWindow);
                    }
                }
            }
        }
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255);
    SDL_RenderClear( renderer );

    // Draw the ball
    drawBall(logic);

    // Draw the paddles
    drawPaddle(0, logic);
    drawPaddle(1, logic);

    // Draw the scores
    drawScores(logic);

    // Update the screen
    SDL_RenderPresent( renderer );
}

void Playerview::drawBall(const Logic &logic) const {
    // get necessary information for ball draw
    Ball ball = logic.getBall();
    double xpos = ball.getXpos();
    double ypos = ball.getYpos();
    double radius = ball.getRadius();

    filledCircleRGBA(renderer, xpos, ypos, radius, BALL_R, BALL_G, BALL_B, 255);
}

void Playerview::drawPaddle(const int paddleId, const Logic &logic) const {
    Paddle paddle = logic.getRightPaddle();
    if (paddleId == 0) {
        paddle = logic.getLeftPaddle();
    }

    // get necessary information for paddle draw
    double xpos = paddle.getXpos();
    double ypos = paddle.getYpos();
    double height = paddle.getHeight();
    double width = paddle.getWidth();
    double ybottom = paddle.getYbottom();
    double xright = paddle.getXright();

    boxRGBA(renderer, xpos, ypos, xright, ybottom, PADDLE_R, PADDLE_G, PADDLE_B, 255);
}

void Playerview::drawScores(const Logic &logic) const {
    const char* aiScore = std::to_string(logic.getAIScore()).c_str();
    const char* playerScore = std::to_string(logic.getPlayerScore()).c_str();

    // render text
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* aiText = TTF_RenderText_Solid( font, aiScore, color );
    if ( aiText == NULL ) pong_error("Unable to render text!");
    SDL_Surface* playerText = TTF_RenderText_Solid( font, playerScore, color );
    if ( playerText == NULL ) pong_error("Unable to render text!");
    
    // convert to texture
    SDL_Texture* aiTexture = SDL_CreateTextureFromSurface( renderer, aiText );
    if(aiTexture == NULL) pong_error("Could not create texture from surface!");
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface( renderer, playerText );
    if(playerTexture == NULL) pong_error("Could not create texture from surface!");

    bool red = true, green = true, blue = true;
    float angle = 0;

    SDL_Rect aiDst = { (2 * SCREEN_WIDTH / 3) - (aiText->w / 2), SCREEN_HEIGHT / 3 - (aiText->h / 2), aiText->w, aiText->h };

    SDL_Rect playerDst = { (SCREEN_WIDTH / 3) - (playerText->w / 2), SCREEN_HEIGHT / 3 - (playerText->h / 2), playerText->w, playerText->h };

    SDL_FreeSurface(aiText);
    aiText = NULL;
    SDL_FreeSurface(playerText);
    playerText = NULL;

    SDL_SetTextureColorMod(aiTexture, red * 255, green * 255, blue * 255);
    SDL_RenderCopy(renderer, aiTexture, NULL, &aiDst);
    SDL_DestroyTexture(aiTexture);

    SDL_SetTextureColorMod(playerTexture, red * 255, green * 255, blue * 255);
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerDst);
    SDL_DestroyTexture(playerTexture);
}

void Playerview::showStartupScreen() {
    startupWindow = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.6, SDL_WINDOW_SHOWN);
    if (startupWindow == NULL) pong_error("Window could not be created!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // create renderer
    SDL_Renderer* startupRenderer = SDL_CreateRenderer(startupWindow, -1, SDL_RENDERER_ACCELERATED);
    if (startupRenderer == NULL) pong_error("Unable to create renderer!");

    SDL_SetRenderDrawColor(startupRenderer, 0, 0, 0, 255);
    SDL_RenderClear(startupRenderer);

    const char* message = "Welcome to Pong! You will play against an AI.\n"
                          "First to 11 points wins.\n"
                          "Use the arrow keys to move your paddle up and down.\n"
                          "Press 'q' to quit and 'esc' to begin";

    // Split the message into lines
    std::vector<std::string> lines;
    std::istringstream stream(message);
    std::string line;
    while (std::getline(stream, line, '\n')) {
        lines.push_back(line);
    }

    // render each line of text
    SDL_Color color = {255, 255, 255};
    int yOffset = 0;
    for (const auto &line : lines) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (textSurface == NULL) pong_error("Unable to render text!");

        SDL_Texture* texture = SDL_CreateTextureFromSurface(startupRenderer, textSurface);
        if (texture == NULL) pong_error("Could not create texture from surface!");

        SDL_Rect dst = {50, 50 + yOffset, textSurface->w/3, textSurface->h/3};
        SDL_RenderCopy(startupRenderer, texture, NULL, &dst);

        yOffset += static_cast<int>(textSurface->h * 0.6) + 10;

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(startupRenderer);
    SDL_DestroyRenderer( startupRenderer );
}

void Playerview::showEndScreen(const int result) {
    endWindow = SDL_CreateWindow( "Game Over!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.6, SDL_WINDOW_SHOWN );
    if( endWindow == NULL ) pong_error("Window could not be created!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // create renderer
    SDL_Renderer* endRenderer = SDL_CreateRenderer(endWindow, -1, SDL_RENDERER_ACCELERATED);
    if (endRenderer == NULL) pong_error("Unable to create renderer!");

    SDL_SetRenderDrawColor(endRenderer, 0, 0, 0, 255);
    SDL_RenderClear(endRenderer);

    const char* message;
    if (result == 1) {
        message = "You win! Press 'q' to quit and 'esc' to play again.";
    } else {
        message = "You lose! Press 'q' to quit and 'esc' to play again.";
    }

    // render the text
    SDL_Color color = {255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);
    if (textSurface == NULL) pong_error("Unable to render text!");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(endRenderer, textSurface);
    if (texture == NULL) pong_error("Could not create texture from surface!");

    SDL_Rect dst = {50, 50, textSurface->w/3, textSurface->h/3 };
    SDL_RenderCopy(endRenderer, texture, NULL, &dst);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(endRenderer);
    SDL_DestroyRenderer( endRenderer );
}

void Playerview::shutdown() const {
    /*** Clean Up ***/

    // Destroy renderer
    SDL_DestroyRenderer( renderer );

    // Destroy window
    SDL_DestroyWindow( gameWindow );

    // Quit SDL_ttf
    TTF_Quit();

    // Quit SDL subsystems
    SDL_Quit();
}
