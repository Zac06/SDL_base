#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"

using namespace std;

/// @brief initializes all necessary elements. Prints errors if something fails.
/// @return true if everything initializes successfully, false if something fails.
bool check_functions(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)>0){
        cerr<<"SDL_Init() has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        cerr<<"IMG_Init(IMG_INIT_PNG) has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(TTF_Init()!=0){
        cerr<<"TTF_init() has failed. Error: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)!=0){
        cerr<<"Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }

    return true;
}

/// @brief Closes everything that has been initialized in check_functions
void close(){
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv){
    if(!check_functions()){
        return -1;
    }

    render_window window("SDL_base", 640, 480);                         //initializes the window and the renderer
    SDL_Event event;
    SDL_Texture* prova=window.load_texture("../res/gfx/prova.png");     //test textures, fonts, entities, sounds
    TTF_Font* provafont=window.load_font("../res/font/maldini.otf", 30);
    fontcache provafc(provafont, 30, (SDL_Color){255,255,255,255}, window.get_renderer());
    Mix_Chunk* provasuono=window.load_sound("../res/sfx/suono.wav");

    entity prova_ent(0,0,20,20,prova);

    while(window.is_running()){                         //while the window is still running
        while(SDL_PollEvent(&event)){                   //handle events. Need a better way. Maybe integrate it inside render_window.
            switch(event.type){
                case SDL_QUIT:{
                    window.set_running(false);
                    break;
                }
                case SDL_KEYDOWN:{
                    if(event.key.keysym.sym=='p'){
                        window.play_sound(provasuono);
                    }
                    break;
                }
            }
        }

        //window.clear((SDL_Color){255,0,0,128});
        window.clear();                                 //refreshes the screen. Can take a color as parameter (background color)

        //window.render_texture(prova, 0, 0);
        //window.render_texture_ultra(prova, 0, 0, (float)1.0, (float)45.0);
        
        window.render_entity(prova_ent);                //renders an entity
        window.render_text(provafont, "prova ttf\nprova capolinea", (SDL_Color){255,255,255,255}, 100,30);      //renders text using TTF rendering (heavier, but font is usually sharper)
        window.render_text_fc(provafc, "prova fontcache\nprova capolinea fontcache", 100, 100);                 //renders text using fontcache (lighter)
        //window.render_text(provafont, "prova 1",(SDL_Color){255,255,255,255}, 100,270);
        window.display();                       //displays everything that has been put in the renderer
    }

    close();

    return 0;
}
