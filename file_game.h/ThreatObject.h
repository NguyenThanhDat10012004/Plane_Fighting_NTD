#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include "Function.h"
#include "AmoObject.h"
class ThreatObject
{
public:
    ThreatObject();
    
    bool loadFromFile( std::string path );
    void render( int x, int y );
    void Handlemove();
    int getOx() {return Ox;}
    int getOy() {return Oy;}
    void SetAmoList(std::vector <AmoObject *> amo_list) {p_amo_list_ = amo_list;}
    std::vector <AmoObject *> GetAmoList() {return p_amo_list_;}
    void InitAmo(AmoObject* p_amo);
    void getVector(AmoObject *x) {p_amo_list_.push_back(x);}
    void MakeAmo();
    void confirmOx(int x) {Ox += x;}
    void free();
    SDL_Rect getRect() { return mCollider;}
    void Reset(const int& ox, int idx);
    void ResetAmo(AmoObject* p_amo, int i);

private:
    int Ox, Oy;
    int run;
    int mWidth;
    int mHeight;
    SDL_Texture* mTexture;
    std::vector <AmoObject *> p_amo_list_;
    SDL_Rect mCollider;
};












#endif