#include "ExploreObject.h"


ExploreObject::ExploreObject()
{
    frame=0;
}

void ExploreObject::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void ExploreObject::set_clip()
{
    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = Explore_Width;
    clip[0].h = Explore_Height;

    clip[1].x = Explore_Width;
    clip[1].y = 0;
    clip[1].w = Explore_Width;
    clip[1].h = Explore_Height;

    clip[2].x = 2*Explore_Width;
    clip[2].y = 0;
    clip[2].w = Explore_Width;
    clip[2].h = Explore_Height;

    clip[3].x = 3*Explore_Width;
    clip[3].y = 0;
    clip[3].w = Explore_Width;
    clip[3].h = Explore_Height;

}
void ExploreObject::render( int x, int y, SDL_Rect* clip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
bool ExploreObject::loadFromFile( std::string path )
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
void ExploreObject::show(int x, int y,int ex)
{
    frame = ex;
    if(frame >= 4*3)
    {
        frame = 0;
    }
    render(x, y, &clip[frame/3]);
}