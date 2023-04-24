#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "Function.h"

class TextObject
{
    public:
    enum
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    TextObject();
    
    SDL_Color GetColor(){return text_color;}
    bool loadFromFile( std::string path ); 
    void SetColor(const int& type);
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    void free();
    void confirmOx_Oy(int x, int y){Ox = x;Oy = y;}
    int getOx(){return Ox;}
    int getOy(){return Oy;}
    SDL_Rect getRect(){return hcn;}
    void SetRect()
    {
        hcn.x = Ox;
        hcn.y = Oy;
        hcn.w = mWidth;
        hcn.h = mHeight;
    }
    bool render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    private:
    std::string str;
    SDL_Color text_color;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    int Ox, Oy;
    SDL_Rect hcn;
};

#endif