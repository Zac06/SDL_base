#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include <string>

using namespace std;

/// @brief This class uses a texture and its position to render everything it needs.
class entity {
    public:
        entity(double p_x, double p_y, SDL_Texture* p_tex);
        entity(double p_x, double p_y, double p_w, double p_h, SDL_Texture* p_tex);
        ~entity();

        void set_x(double p_x);
        double get_x();
        void set_y(double p_x);
        double get_y();
        void set_w(double p_w);
        double get_w();
        void set_h(double p_w);
        double get_h();
        void set_scale(float scale);
        float get_scale();
        void set_rotation(double p_rotation);
        double get_rotation();
        
        SDL_Texture* get_tex();
        
        void set_rot_center(SDL_Point pt);
        SDL_Point get_rot_center();
    private:
        double x;
        double y;
        double w;
        double h;
        double rotation;
        float scale;

        SDL_Point rot_center;

        SDL_Texture* tex;
};
