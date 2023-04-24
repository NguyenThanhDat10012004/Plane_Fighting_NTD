#ifndef PLAY_POWER_H
#define PLAY_POWER_H

#include "Function.h"

class PlayPower
{
    public:
    PlayPower();
    
    bool loadFromFile( std::string path );
    void render( int x, int y );
    void SetNumber(const int& num);
    void AddPos(const int& pos);
    void show();
    void init();
    void decrease();
    void free();
    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    int number;
    std::vector <int> pos_list;

};

#endif