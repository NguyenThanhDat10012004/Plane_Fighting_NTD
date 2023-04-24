#include "BossObject.h"

BossObject::BossObject(){
    Ox=0;
    Oy=0;
    check_up = 1;
    check_down = 0;
}


void BossObject::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void BossObject::Handlemoveboss()
{
    if(Oy < 0)
    {
        check_up = 0;
        check_down = 1;
    }
    else if(Oy > SCREEN_HEIGHT - 250)
    {
        check_up = 1;
        check_down = 0;
    }
    if(check_up == 1)
    {
        Oy -= 1;
    }
    else if(check_down == 1)
    {
        Oy += 1;
    }
}
void BossObject::InitAmoboss()
{
    AmoObject* p_amo = new AmoObject();
    bool check = p_amo ->loadFromFile("./images/laser1.png");
    if(check)
    {
        p_amo ->set_is_move(true);
        p_amo->get_width_height(36,5);
        p_amo ->confirmOx( Ox - 10);
        p_amo ->confirmOy( Oy + 130);
        getVector(p_amo);
    }
    AmoObject* p_amo1 = new AmoObject();
    bool check1 = p_amo1 ->loadFromFile("./images/sphere2.png");
    if(check1)
    {
        p_amo1 ->set_is_move(true);
        p_amo1->get_width_height(10,10);
        p_amo1 ->confirmOx( Ox + 120);
        p_amo1 ->confirmOy( Oy + 55);
        getVector(p_amo1);
    }

}
void BossObject::MakeAmoboss()
{
     for(int i = 0; i < p_amo_list_.size(); i++)
    {
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo)
        {
            if(p_amo->get_is_move())
            {
                
                p_amo->render(p_amo->getOx(), p_amo->getOy());
                p_amo->handle_movetotheleft();
            }
            else
            {
                if(i == 0)
                {
                    p_amo ->set_is_move(true);
                    p_amo ->confirmOx(Ox - 10);
                    p_amo ->confirmOy(Oy + 130);
                }
                else
                {
                    p_amo ->set_is_move(true);
                    p_amo ->confirmOx(Ox + 120);
                    p_amo ->confirmOy(Oy + 55);
                }
                    
            }
        }
        
    }
}
void BossObject::render( int x, int y)
{   mCollider.x = x; mCollider.y = y;
    mCollider.w = mWidth; mCollider.h = mHeight;
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
bool BossObject::loadFromFile( std::string path )
{
    free();
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}
void BossObject::ResetAmoboss(AmoObject* p_amo, int i)
{
    if(i == 0)
    {
        p_amo ->confirmOx( Ox - 10);
        p_amo ->confirmOy( Oy + 130);
    }
    else
    {
        p_amo ->confirmOx( Ox + 120);
        p_amo ->confirmOy( Oy + 55);
    }
    
}