#include "audio.h"
#include "util.h"

Audio::Audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        pong_error("SDL_mixer could not initialize!");
    }
}

Audio::~Audio() {
    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }
    soundMap.clear();
    Mix_CloseAudio();
}

bool Audio::loadSound(const std::string& id, const std::string& filename) {
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    if (sound == NULL) {
        std::cerr << "Unable to load sound: " << filename << " (" << Mix_GetError() << ")" << std::endl;
        return false;
    }
    soundMap[id] = sound;
    return true;
}

void Audio::playSound(const std::string& id) {
    Mix_PlayChannel(-1, soundMap[id], 0);
}