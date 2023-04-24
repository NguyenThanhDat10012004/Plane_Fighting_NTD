#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "AmoObject.h"
#include "Function.h"

class LTexture
{
    public:
        LTexture();
        
        bool loadFromFile( std::string path );
        void move_SDL(SDL_Event e);
        void move();
        void render( int x, int y );
        void free();
        int getWidth();
        int getHeight();
        int getOx();
        int getOy();
        void set_Ox_Oy(int x, int y) {Ox = x; Oy = y;}
        void SetAmoList(std::vector <AmoObject *> amo_list) {p_amo_list_ = amo_list;}
        std::vector <AmoObject *> GetAmoList() {return p_amo_list_;}
        void getVector(AmoObject *x)
        {
            p_amo_list_.push_back(x);
        }
        SDL_Rect getRect()
        {
            return mCollider;
        }
        void removeAmo(const int& idx);
        void Setvel(){mVelX=0;mVelY=0;}
    private:
        
        SDL_Texture* mTexture;
        int mVelX, mVelY;
        int mWidth;
        int mHeight;
        int Ox;
        int Oy;
        std::vector <AmoObject *> p_amo_list_;
        SDL_Rect mCollider;
};

#endif