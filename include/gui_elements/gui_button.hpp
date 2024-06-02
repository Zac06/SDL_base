#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "base_elements/gui_element.hpp"

using namespace std;

class gui_button : public gui_element{
    public:
        gui_button(SDL_Texture* p_tex_normal, event_mgr& p_events, SDL_Point p_coords);
        gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, event_mgr& p_events, SDL_Point p_coords);
        gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, event_mgr& p_events, SDL_Point p_coords);

        void update() override;

    private:


};