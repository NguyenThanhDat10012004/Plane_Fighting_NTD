#include "Ltexture.h"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    Ox = start_Ox;
    Oy = start_Oy;
    mVelX = 0;
    mVelY = 0;
    mCollider.w = GFOO_WIDTH;
    mCollider.h = GFOO_HEIGHT;
}
bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    

    //The final texture
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
void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void LTexture::render( int x, int y )
{
    mCollider.x = x; mCollider.y = y;
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
void LTexture::move_SDL(SDL_Event e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= GFOO_VEL; break;
            case SDLK_DOWN: mVelY += GFOO_VEL; break;
            case SDLK_LEFT: mVelX -= GFOO_VEL; break;
            case SDLK_RIGHT: mVelX += GFOO_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += GFOO_VEL; break;
            case SDLK_DOWN: mVelY -= GFOO_VEL; break;
            case SDLK_LEFT: mVelX += GFOO_VEL; break;
            case SDLK_RIGHT: mVelX -= GFOO_VEL; break;
        }
    }
    else if((e.type == SDL_MOUSEBUTTONDOWN ) && (e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT))
    {
        AmoObject* p_amo = new AmoObject();
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            p_amo->loadFromFile("./images/laser.png");
            p_amo->set_type(AmoObject::LASER);
            p_amo->get_width_height(WIDTH_LASER,HEIGHT_LASER);
            Mix_PlayChannel( -1, laser, 0 );
        }
        else if(e.button.button == SDL_BUTTON_RIGHT)
        {
            p_amo->loadFromFile("./images/sphere.png");
            p_amo->set_type(AmoObject::SPHERE);
            p_amo->get_width_height(WIDTH_SPHERE,HEIGHT_SPHERE);
            Mix_PlayChannel( -1, sphere, 0 );
        }
        p_amo->confirmOx(Ox + 75 );
        p_amo->confirmOy(Oy + 26);
        p_amo->set_is_move(true);
        getVector(p_amo);
    }
}
void LTexture::move()
{
    //Move the dot left or right
    Ox += mVelX;
    Ox = std::min(1000, Ox);
    //If the dot went too far to the left or right
    if( ( Ox < 0 ) || ( Ox + GFOO_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        Ox -= mVelX;
        Ox = std::max(0, Ox);
    }

    //Move the dot up or down
    Oy += mVelY;
    Oy = std::min(550,Oy);
    //If the dot went too far up or down
    if( ( Oy < 0 ) || ( Oy + GFOO_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        Oy -= mVelY;
        Oy = std::max(0, Oy);
    }
}
int LTexture::getWidth()
{
    return mWidth;
}
int LTexture::getHeight()
{
    return mHeight;
}
int LTexture::getOx()
{
    return Ox;
}
int LTexture::getOy()
{
    return Oy;
}
void LTexture::removeAmo(const int& idx)
{
for(int i = 0; i < p_amo_list_.size(); i++)
    {
        if(idx < p_amo_list_.size())
        {
            AmoObject* p_amo = p_amo_list_.at(idx);
            p_amo_list_.erase(p_amo_list_.begin() + idx);
            if(p_amo != NULL)
            {
                delete p_amo;
                p_amo = NULL;
            }
        }
    }
}
