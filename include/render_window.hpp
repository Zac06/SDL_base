#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>
#include<queue>

#include "entity.hpp"
#include "fontcache.hpp"

using namespace std;

class render_window{
    public:
        render_window(string p_title, int p_w, int p_h);
        ~render_window();

        SDL_Renderer* get_renderer();

        //void clean();
        void clear();
        void clear(SDL_Color p_bgcolor);

        bool is_running();
        void set_running(bool p_run);

        int get_texture_width(SDL_Texture* p_tex);
        int get_texture_height(SDL_Texture* p_tex);

        SDL_Texture* load_texture(string p_filepath);
        TTF_Font* load_font(string p_filepath, int size);
        Mix_Chunk* load_sound(string p_filepath);

        void render_texture(SDL_Texture* p_tex, int p_x, int p_y);
        void render_texture_ex(SDL_Texture* p_tex, int p_x, int p_y, float scale);
        void render_texture_ex2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h);
        void render_texture_pro(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation);
        void render_texture_ultra(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation, SDL_Point rot_center);
        void render_texture_ultra2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h, float scale, float rotation, SDL_Point rot_center);

        void render_text(TTF_Font* font, string text, SDL_Color color, int destx, int desty);
        void render_text_ex(TTF_Font* font, string text, SDL_Color color, int destx, int desty, float scale);
        void render_text_fc(fontcache& p_fc, string text, int destx, int desty);
        void render_text_fc_ex(fontcache& p_fc, string text, int destx, int desty, float scale);

        void render_entity(entity& p_ent);

        void play_sound(Mix_Chunk* p_sound);
        void play_sound_ex(Mix_Chunk* p_sound, int p_times);
        void play_sound_pro(int p_channel, Mix_Chunk* p_sound, int p_times);

        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;

        SDL_Event event;

        vector<SDL_Texture*> loaded_textures;
        vector<TTF_Font*> loaded_fonts;
        vector<Mix_Chunk*> loaded_sounds;
};
