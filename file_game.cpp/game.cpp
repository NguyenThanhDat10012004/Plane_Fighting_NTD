#include "Function.h"
#include "AmoObject.h"
#include "LTexture.h"
#include "ThreatObject.h"
#include "LTimer.h"
#include "ExploreObject.h"
#include "PlayPower.h"
#include "TextObject.h"
#include "BossObject.h"


int run = 0;
int die_num = 0;
int mark_num = 0;
int num_boss = 100;
int num2 = 0;
bool is_run_ = true;
bool quit = false;
bool kt = 1;


LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture Menu;
LTexture Game_over;
BossObject* boss = new BossObject();
ThreatObject* p_Threats = new ThreatObject[NUM_THREATS];
ExploreObject exp_main;
ExploreObject exp_threat;
PlayPower play_power;
PlayPower play_power_boss;
TextObject text;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load Foo' texture
    if( !gFooTexture.loadFromFile( "./images/plane_fly.png" ) )
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    
    //Load background texture
    if( !gBackgroundTexture.loadFromFile( "./images/bg4800.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    if( !play_power_boss.loadFromFile("./images/play_power.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    if( !play_power.loadFromFile("./images/play_power.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    play_power.init();
    if( !boss->loadFromFile("./images/boss1.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    for(int i = 0; i < NUM_THREATS; i++)
    {
        ThreatObject* p_threat = (p_Threats + i);
        if( !p_threat->loadFromFile( "./images/af1.png"))
        {
            printf( "Failed to load background texture image!\n" );
            success = false;
        }
    }
    if(!exp_main.loadFromFile( "./images/exp_main.png"))
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    else exp_main.set_clip();

    if(!exp_threat.loadFromFile( "./images/exp_main.png"))
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    else exp_threat.set_clip();

    explore = Mix_LoadWAV( "./music/explore.wav" );
    if( explore == NULL )
    {
printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    laser = Mix_LoadWAV( "./music/laser.wav" );
    if( laser == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    sphere = Mix_LoadWAV( "./music/sphere.wav" );
    if( sphere == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    if(!Menu.loadFromFile( "./images/start_img.png" ))
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    if(!Game_over.loadFromFile( "./images/game_over.png" ))
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    gFont = TTF_OpenFont( "./images/lazy.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    text.SetColor(1);
    return success;
}
void close()
{
    //Free loaded images
    gFooTexture.free();
    gBackgroundTexture.free();
    for(int i = 0; i < NUM_THREATS; i++)
    {
        ThreatObject* p_threat = (p_Threats + i);
        p_threat->free();
    }
    play_power.free();
    play_power_boss.free();
    exp_main.free();
    exp_threat.free();
    Menu.free();
    Game_over.free();
    Mix_FreeChunk( explore );
    Mix_FreeChunk( laser );
    Mix_FreeChunk( sphere );    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
bool checkpositionforrect(const int& x, const int& y, SDL_Rect rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
        return false;
}
void startAmo()
{
    for(int i = 0; i < NUM_THREATS; i++)
    {
        if((p_Threats + i))
        {
            (p_Threats +i)->confirmOx(i * 400);
            AmoObject* p_amo2 = new AmoObject();
            (p_Threats + i)->InitAmo(p_amo2);
        }       
                    
    }
}
bool checkcollision(const SDL_Rect a, const SDL_Rect b)
{
int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
void amo()
{
    for(int i = 0; i < NUM_THREATS; i++)
    {
        ThreatObject* p_threat = p_Threats + i;         
        if((p_threat ))
        {
(p_threat )->render((p_threat )->getOx(), (p_threat)->getOy());
            (p_threat )->Handlemove();
            (p_threat )->MakeAmo();
            
            bool is_col3 = false;
            std::vector<AmoObject *> amo_list2 = p_threat->GetAmoList();
            for(int pp = 0; pp < amo_list2.size();pp++)
            {
                AmoObject *p_amo = amo_list2.at(pp);
                if(p_amo != NULL)
                {
                    is_col3 = checkcollision(p_amo->getRect(), gFooTexture.getRect());
                    if(is_col3)
                    {   
                        p_threat->ResetAmo(p_amo, i);
                        break;
                    }
                }
            }
            bool is_col = checkcollision((p_threat)->getRect(), gFooTexture.getRect());
            if(is_col)
            {   
                (p_threat )->Reset(SCREEN_WIDTH + i * 400, i);
            }                    
            if(is_col || is_col3)
            {
                for(int ex = 0; ex < NUM_FRAME*3; ex++)
                {
                    int x_exp = gFooTexture.getRect().x + gFooTexture.getRect().w * 0.5 - Explore_Width * 0.5;
                    int y_exp = gFooTexture.getRect().y + gFooTexture.getRect().h * 0.5 - Explore_Height * 0.5;
                    exp_main.show(x_exp, y_exp, ex);
                }
                Mix_PlayChannel( -1, explore, 0 );
                die_num++;
                if(die_num < NUM_PlayPower)
                {
                   
                    gFooTexture.set_Ox_Oy(start_Ox, start_Oy);
                    play_power.decrease();
                    play_power.show();
                }
                else
                {
                    play_power.decrease();
                    gFooTexture.Setvel();
                    quit = true;
                }
            }
            std::vector<AmoObject *> amo_list = gFooTexture.GetAmoList();
            for(int jj = 0; jj < amo_list.size(); jj++)
            {
                AmoObject *p_amo = amo_list.at(jj);
                if(p_amo != NULL)
                {
                    bool is_col2 = checkcollision(p_amo->getRect(), (p_threat)->getRect());
                    if(is_col2)
                    {
                        mark_num++;
                        for(int ex1 = 0; ex1 < NUM_FRAME*3; ex1++)
                        {
                            int x_exp = p_threat->getRect().x + p_threat->getRect().w * 0.5 - Explore_Width * 0.5;
                            int y_exp = p_threat->getRect().y + p_threat->getRect().h * 0.5 - Explore_Height * 0.5;
                            exp_threat.show(x_exp, y_exp, ex1);
                        }
                        (p_threat )->Reset(SCREEN_WIDTH + i * 400, i);
                        gFooTexture.removeAmo(jj);
                        Mix_PlayChannel( -1, explore, 0 );
                    }
                }
            }
int num1 = time_play-((SDL_GetTicks()/1000) - num2);
            if(num1 == 0) quit = 1;
            std::string abc = "Time: " + std::to_string(num1);
            text.loadFromRenderedText(abc, text.GetColor());
            text.render(1000,0);

            std::string num = std::to_string(mark_num);
            std::string ab = "mark: " + num;
            text.loadFromRenderedText( ab, text.GetColor());
            text.render(500,0);
            
        }
    }
}
void bossamo()
{
    bool is_col4 = false;
    std::vector<AmoObject *> amo_list3 = boss->GetAmoList();
    for(int bs = 0; bs < amo_list3.size();bs++)
    {
        AmoObject *p_amo = amo_list3.at(bs);
        if(p_amo != NULL)
        {
            is_col4 = checkcollision(p_amo->getRect(), gFooTexture.getRect());
            if(is_col4)
            {   
                boss->ResetAmoboss(p_amo, bs);
                break;
            }
        }
    }
    bool is_col5 = checkcollision(boss->getRect(), gFooTexture.getRect());
    if(is_col5)
    {   
        num_boss--;
    } 
    if(is_col4 || is_col5)
    {
        for(int ex = 0; ex < NUM_FRAME*3; ex++)
        {
            int x_exp = gFooTexture.getRect().x + gFooTexture.getRect().w * 0.5 - Explore_Width * 0.5;
            int y_exp = gFooTexture.getRect().y + gFooTexture.getRect().h * 0.5 - Explore_Height * 0.5;
            exp_main.show(x_exp, y_exp, ex);
        }
        Mix_PlayChannel( -1, explore, 0 );
        die_num++;
        if(die_num < NUM_PlayPower)
        {
                   
            gFooTexture.set_Ox_Oy(start_Ox, start_Oy);
            play_power.decrease();
            play_power.show();
        }
        else
        {
            play_power.decrease();
            gFooTexture.Setvel();
            quit = true;
        }
    } 
    
    std::vector<AmoObject *> amo_list = gFooTexture.GetAmoList();
    for(int jj = 0; jj < amo_list.size(); jj++)
    {
        AmoObject *p_amo = amo_list.at(jj);
        if(p_amo != NULL)
        {
            bool is_col2 = checkcollision(p_amo->getRect(), boss->getRect());
            if(is_col2)
            {
                num_boss--;
                for(int ex = 0; ex < NUM_FRAME*3; ex++)
                {
                    int x_exp = p_amo->getRect().x + p_amo->getRect().w * 0.5 - Explore_Width * 0.5;
                    int y_exp = p_amo->getRect().y + p_amo->getRect().h * 0.5 - Explore_Height * 0.5;
                    exp_main.show(x_exp, y_exp, ex);
                }
                if(num_boss == 0)
                {
                    kt = 0;
                    mark_num += 50;
                }
                gFooTexture.removeAmo(jj);
                Mix_PlayChannel( -1, explore, 0 );
            }
        }
    }      
}
int showMenu(SDL_Event e)
{
     SDL_Rect item[itemMenu];
    item[0].x = 480;
    item[0].y = 350;
    item[1].x = 480;
    item[1].y = 430;

    int x, y;
    TextObject text_menu[itemMenu];
    text_menu[0].loadFromFile("./images/start.png");
    text_menu[0].confirmOx_Oy(item[0].x, item[0].y);
    text_menu[0].SetRect();

    text_menu[1].loadFromFile("./images/exit.png");
    text_menu[1].confirmOx_Oy(item[1].x, item[1].y);
    text_menu[1].SetRect();

    bool Selected[itemMenu] = {0, 0};
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                quit = true;
                break;
                case SDL_MOUSEMOTION:
                {
                    SDL_GetMouseState( &x, &y );
                    for(int i = 0; i < itemMenu; i++)
                    {
                        if(checkpositionforrect(x, y, text_menu[i].getRect()))
                        {
                            if(Selected[i] == 0)
                            {
                                Selected[i] = 1;
                                text_menu[i].SetColor(2);
                            }
                        }
                        else
                        {
                            if(Selected[i] == 1)
                            {
                                Selected[i] = 0;
                                text_menu[i].SetColor(1);
                                
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_GetMouseState( &x, &y );
                    for(int i = 0; i < itemMenu; i++)
                    {
                        if(checkpositionforrect(x, y, text_menu[i].getRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
                case SDL_KEYDOWN:
                {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 1;
                    }
                }
                default:
                break;
            }
        }
        SDL_RenderClear( gRenderer );

        Menu.render(0, 0);
        for(int i = 0; i < itemMenu; i++)
        {

            text_menu[i].render(text_menu[i].getOx(), text_menu[i].getOy());
        }

        SDL_RenderPresent(gRenderer);
    }
    return 1;
}
int showGameover(SDL_Event e)
{
    SDL_Rect item[itemGame_over];
    item[0].x = 520;
    item[0].y = 350;
    item[1].x = 520;
    item[1].y = 430;

    int x, y;
    TextObject text_menu[itemGame_over];
    text_menu[0].loadFromFile("./images/play.png");
    text_menu[0].confirmOx_Oy(item[0].x, item[0].y);
    text_menu[0].SetRect();

    text_menu[1].loadFromFile("./images/exit.png");
    text_menu[1].confirmOx_Oy(item[1].x, item[1].y);
    text_menu[1].SetRect();

    bool Selected[itemGame_over] = {0, 0};
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                quit = true;
                break;
                case SDL_MOUSEMOTION:
                {
                    SDL_GetMouseState( &x, &y );
                    for(int i = 0; i < itemGame_over; i++)
                    {
                        if(checkpositionforrect(x, y, text_menu[i].getRect()))
                        {
                            if(Selected[i] == 0)
                            {
                                Selected[i] = 1;
                                text_menu[i].SetColor(2);
                            }
                        }
                        else
                        {
                            if(Selected[i] == 1)
                            {
                                Selected[i] = 0;
                                text_menu[i].SetColor(1);
                                
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_GetMouseState( &x, &y );
                    for(int i = 0; i < itemGame_over; i++)
                    {
                        if(checkpositionforrect(x, y, text_menu[i].getRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
                case SDL_KEYDOWN:
                {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 1;
                    }
                }
                default:
                break;
            }
        }
        SDL_RenderClear( gRenderer );

        Game_over.render(0, 0);
        for(int i = 0; i < itemGame_over; i++)
        {

            text_menu[i].render(text_menu[i].getOx(), text_menu[i].getOy());
        }
        std::string num = std::to_string(mark_num);
        std::string ab = "YOUR SCORE IS: " + num;
        text.loadFromRenderedText( ab, text.GetColor());
        text.render(470,200);

        SDL_RenderPresent(gRenderer);
    }
    return 1;
}
/*---------------------------------------------------------------------------------------*/
int main( int argc, char* args[] )
{
    LTimer fps_time_;
    int distance = 0;
    
    if( !init() )
    {
printf( "Failed to initialize!\n" );
    }
    else
    {
        
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {   
            startAmo();
            SDL_Event e;
            boss->set_Ox_Oy(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 500);     
            boss->InitAmoboss();
            int check_menu = showMenu(e);
            if(check_menu == 1) quit = true;
            while( !quit )
            {
                fps_time_.start();
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    gFooTexture.move_SDL( e );

                }
                gFooTexture.move();
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                if(is_run_ == true)
                {
                    distance -= 4;
                    if(distance <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
                    {
                        is_run_ = false;
                    }
                    else
                    {
                        gBackgroundTexture.render( distance, 0 );
                    }
                }
                else
                {      
                    gBackgroundTexture.render( distance, 0 );
                    
                        boss->render(boss->getOx(), boss->getOy());
                        boss->Handlemoveboss();
                        boss->MakeAmoboss();
                        play_power_boss.render(300,0);
                        std::string num = std::to_string(num_boss);
                        std::string ab = "boss: " + num;
                        text.loadFromRenderedText( ab, text.GetColor());
                        text.render(340,0);
                                                        
                }
                
                    gFooTexture.render( gFooTexture.getOx(), gFooTexture.getOy() );
                    play_power.show();
                    
                for(unsigned long int i = 0; i < gFooTexture.GetAmoList().size();i++)
                {
                    std::vector<AmoObject *> amo_list = gFooTexture.GetAmoList();
                    AmoObject *p_amo = amo_list.at(i);
                    if(p_amo != NULL)
                    {
                        if(p_amo->get_is_move())
                        {
                        p_amo->render(p_amo->getOx(), p_amo->getOy());
                        p_amo->handle_move();
                        }
                        else 
                        {
                            if(p_amo != NULL)
                            {
                                amo_list.erase(amo_list.begin() + i);
                                gFooTexture.SetAmoList(amo_list);
                        delete p_amo;
                                p_amo = NULL;
                            }
                        }
                        
                    }
                }
                
                amo();
                if(is_run_ == false) bossamo();
                if(quit == 1)
                {
                    int ck = showGameover(e);
                    if(ck == 0)
                    {
                        
                        num_boss = 100;
                        distance = 0;
                        is_run_ = true;
                        boss->set_Ox_Oy(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 500);
                        quit = 0;
                        play_power.init();
                        die_num = 0;
                        mark_num = 0;
                        num2 = (SDL_GetTicks()/1000);
                        gFooTexture.set_Ox_Oy(start_Ox, start_Oy);
                    }
                    else
                    {
                        quit = 1;
                    } 
                }
                SDL_RenderPresent( gRenderer );
                int real_time = fps_time_.getTicks();
                if(real_time < SCREEN_TICK_PER_FRAME)
                {
                    int delay_time = SCREEN_TICK_PER_FRAME - real_time;
                    SDL_Delay(delay_time);
                }
            }
        }
    }
    close();
    return 0;
}