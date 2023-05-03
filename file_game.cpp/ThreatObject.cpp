#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    run =0;
    mWidth = WIDTH_THREAT;
    mHeight = HEIGHT_THREAT;
    Ox = SCREEN_WIDTH;
    run += 50;
    Oy = run;
    mCollider.w = Threat_WIDTH;
    mCollider.h = Threat_HEIGHT;
}

void ThreatObject::Handlemove()
{
    Ox -= 7;
    if(Ox <= 0)
    {
        Ox = SCREEN_WIDTH;

        int rand_y = rand() % 400;
        if(rand_y > SCREEN_HEIGHT - 200)
        {
            rand_y = SCREEN_HEIGHT / 3;
        }
        Oy = rand_y;
    }
}
bool ThreatObject::loadFromFile( std::string path )
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
void ThreatObject::render( int x, int y )
{
    mCollider.x = x; mCollider.y = y;
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
void ThreatObject::InitAmo(AmoObject* p_amo)
{
    bool check = p_amo ->loadFromFile("./images/sphere.png");
if(check)
    {
        p_amo ->set_is_move(true);
        p_amo ->set_type(AmoObject::SPHERE);
        p_amo->get_width_height(WIDTH_SPHERE,HEIGHT_SPHERE);
        p_amo ->confirmOx( Ox - 80);
        p_amo ->confirmOy( Oy + 5);
        getVector(p_amo);
    }
}
void ThreatObject::MakeAmo() 
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
            p_amo ->set_is_move(true);
            p_amo ->confirmOx(Ox - 80);
            p_amo ->confirmOy(Oy + 5);
            }
        }
        
    }
}
void ThreatObject::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void ThreatObject::Reset(const int& ox, int idx)
{
    Ox = ox;
    int rand_y = rand() % 400;
    if(rand_y > SCREEN_HEIGHT - 200)
    {
        rand_y = SCREEN_HEIGHT / 3;
    }
        Oy = rand_y;
    for(int i = 0; i < p_amo_list_.size(); i++)
    {
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo)
        {
            ResetAmo(p_amo, idx);
        }
    }
}
void ThreatObject::ResetAmo(AmoObject* p_amo, int i)
{
    p_amo ->confirmOx(Ox - 80);
    p_amo ->confirmOy(Oy + 5);
}
