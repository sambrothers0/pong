#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>
#include <string>
#include <map>

class Audio {
public:
    Audio();
    ~Audio();

    bool loadSound(const std::string& id, const std::string& filename);
    void playSound(const std::string& id);

private:
    std::map<std::string, Mix_Chunk*> soundMap;
};

#endif // AUDIO_H