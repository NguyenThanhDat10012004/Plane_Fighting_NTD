#include "AmoObject.h"

AmoObject::AmoObject()
{
    mWidth = 0;
    mHeight = 0;
    Ox = 0;
    Oy = 0;
    is_move_ = false;
    amo_type_ = NONE;
}
void AmoObject::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


bool AmoObject::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    //The final texture
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

void AmoObject::render( int x, int y )
{
    mCollider.x = x; mCollider.y = y;
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

void AmoObject::confirmOx(int x)
    {
        Ox = x;
    }
void AmoObject::confirmOy(int x)
    {
        Oy = x;
    }
void AmoObject::handle_move()
    {
        Ox += 20;
        if(Ox >= 1000) is_move_ = false;

    }
void AmoObject::handle_movetotheleft()
    {
        Ox -= 10;
        if(Ox <= 0) is_move_ = false;
    }

int AmoObject::getOx()
{
    return Ox;
}
int AmoObject::getOy()
{
    return Oy;
}