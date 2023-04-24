#ifndef EXPLORE_OBJECT_H
#define EXPLORE_OBJECT_H

#include "Function.h"
class ExploreObject
{
public:
    ExploreObject();
    
    void set_clip();
    void free();
    bool loadFromFile( std::string path );
    void render( int x, int y, SDL_Rect* clip );
    void show(int x, int y, int ex);
private:
    int frame;
    SDL_Rect clip[NUM_FRAME];
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif