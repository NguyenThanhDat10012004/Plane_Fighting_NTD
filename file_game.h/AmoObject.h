#ifndef AMOOBJECT_H
#define AMOOBJECT_H

#include "Function.h"

class AmoObject
{
    public:
    enum AmoType
    {
        NONE = 0,
        LASER = 1,
        SPHERE = 2
    };
    AmoObject();
    
    void free();
    int get_type() const{return amo_type_;}
    void set_type( const int& type ){amo_type_ = type;}
    bool get_is_move() const{return is_move_;}
    void set_is_move( bool is_move) {is_move_ = is_move;}
    bool loadFromFile( std::string path );
    void render( int x, int y );
    int getOx();
    int getOy();
    void confirmOx(int x);

    void confirmOy(int x);

    void handle_move();

    void handle_movetotheleft();

    SDL_Rect getRect()
    {
        return mCollider;
    }
    void get_width_height(int width, int height)
    {
        mCollider.w = width;
        mCollider.h = height;
    }
    bool is_move_;
    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    int Ox;
    int Oy;
    int amo_type_;
    SDL_Rect mCollider;
};

#endif