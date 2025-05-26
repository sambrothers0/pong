//
// Created by samjb on 2/5/2025.
//
#include <SDL.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "logic.h"
#include "playerview.h"
#include "aiview.h"
#include "util.h"

void shutdown(Playerview &playerview) {
    playerview.shutdown();
}

double getTimeElapsed(std::chrono::steady_clock::time_point &prevTick) {
    auto curTick = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> deltaMs = curTick - prevTick;

    prevTick = curTick;
    return deltaMs.count();
}

int main(int argc, char** argv) {
    Logic logic = Logic();
    Playerview playerview = Playerview();

    std::chrono::steady_clock clock;
    auto prevTick = clock.now();

    double timeScalar = 1.0;
    // long totalTicks = 0;

    bool running = true;
    while (running) {

        double tickRate = getTimeElapsed(prevTick);
        tickRate *= timeScalar;

        logic.update(running, tickRate);
        playerview.update(logic);

    }
    shutdown(playerview);
    return 0;
}
