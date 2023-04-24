#ifndef BOSS_OBJECT_H
#define BOSS_OBJECT_H

#include "Function.h"
#include "AmoObject.h"


class BossObject 
{
public:
    BossObject();
    
    int getOx() {return Ox;}
    int getOy() {return Oy;}
    void InitAmoboss();
    void Handlemoveboss();
    void MakeAmoboss();
    void render( int x, int y );
    bool loadFromFile( std::string path );
    void set_Ox_Oy(int x, int y){Ox = x; Oy = y;}
    void getVector(AmoObject *x) {p_amo_list_.push_back(x);}
    void SetAmoList(std::vector <AmoObject *> amo_list) {p_amo_list_ = amo_list;}
    std::vector <AmoObject *> GetAmoList() {return p_amo_list_;}
    void ResetAmoboss(AmoObject *p_amo, int i);
    SDL_Rect getRect() { return mCollider;}
    void free();
private:
    int Ox, Oy;
    int mWidth;
    int mHeight;
    SDL_Texture* mTexture;
    std::vector <AmoObject *> p_amo_list_;
    SDL_Rect mCollider;
    int check_up;
    int check_down;
};

#endif