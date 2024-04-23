#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<vector>
#include<iostream>
using namespace std;

class fontcache{
    private:
        vector<SDL_Texture*> char_textures;
        int font_size;
        TTF_Font* font;
        SDL_Color color;
        
    public:
        fontcache(TTF_Font* p_f, int p_font_size, SDL_Color p_color, SDL_Renderer* p_rend);
        ~fontcache();

        SDL_Texture* get_char_texture(unsigned char c);
        void set_char_texture(SDL_Texture* p_tex, unsigned char c);
        int get_fc_size();
        int get_font_size();
        SDL_Color get_color();
};
