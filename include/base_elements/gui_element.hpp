#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "rendering/event_mgr.hpp"

using namespace std;

#define GUI_STATE_NORMAL 0
#define GUI_STATE_HOVER 1
#define GUI_STATE_ACTIVE 2
#define GUI_STATE_DISABLE -1

class gui_element {
    public:
        gui_element(SDL_Texture* p_tex_normal, event_mgr& p_events, SDL_Point p_coords);
        gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, event_mgr& p_events, SDL_Point p_coords);
        gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, event_mgr& p_events, SDL_Point p_coords);

        void set_state(int p_state);
        int get_state();

        virtual void update()=0;        //pure virtual method (equivalent of abstract)

    private:
        SDL_Texture* tex_normal;
        SDL_Texture* tex_hover;
        SDL_Texture* tex_active;
        SDL_Texture* tex_disabled;

        int state;
        
        event_mgr& events;
        
        int x,y;

};
