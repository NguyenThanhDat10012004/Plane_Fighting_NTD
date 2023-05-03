#include "PlayPower.h"

PlayPower::PlayPower()
{
    
}

void PlayPower::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void PlayPower::SetNumber(const int& num)
{
    number = num;
}
bool PlayPower::loadFromFile( std::string path )
{
    
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
void PlayPower::render( int x, int y )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
void PlayPower::AddPos(const int& pos)
{
    pos_list.push_back(pos);
}
void PlayPower::show()
{
    if(number == pos_list.size())
    {
        for(int i = 0; i < pos_list.size(); i++)
        {
            render(pos_list[i], 0);
        }
    }
}
void PlayPower::init()
{
    number = NUM_PlayPower;
    if(pos_list.size() > 0)
    {
        pos_list.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
    AddPos(140);
}
void PlayPower::decrease()
{
    number--;
    pos_list.pop_back();
}
