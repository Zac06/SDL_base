#include "render_window.hpp"

render_window::render_window(string p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL), running(true),
    loaded_textures(), loaded_fonts(), loaded_sounds()
{
    window=SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if(window==NULL){
        cerr<<"Window creation failed. Error: "<<SDL_GetError()<<"\n";
        return;
    }

    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer==NULL){
        cerr<<"Renderer creation failed. Error: "<<SDL_GetError()<<"\n";
        return;
    }

}

render_window::~render_window(){
    for(int i=0; i<(int)loaded_textures.size(); i++){
        SDL_DestroyTexture(loaded_textures[i]);
    }
    /*for(int i=0; i<(int)loaded_fonts.size(); i++){
        TTF_CloseFont(loaded_fonts[i]);
    }*/
    for(int i=0; i<(int)loaded_sounds.size(); i++){
        Mix_FreeChunk(loaded_sounds[i]);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

SDL_Renderer* render_window::get_renderer(){
    return renderer;
}

/*void render_window::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}*/

bool render_window::is_running(){
    return running;
}

void render_window::set_running(bool p_run){
    running=p_run;
}

int render_window::get_texture_width(SDL_Texture* p_tex){
    int w;
    SDL_QueryTexture(p_tex, NULL, NULL, &w, NULL);
    return w;
}

int render_window::get_texture_height(SDL_Texture* p_tex){
    int h;
    SDL_QueryTexture(p_tex, NULL, NULL, NULL, &h);
    return h;
}

SDL_Texture* render_window::load_texture(string p_filepath){
    SDL_Texture* tex=NULL;

    tex=IMG_LoadTexture(renderer, p_filepath.c_str());

    if(tex==NULL){
        cerr<<"Failed to load texture at path "<<p_filepath<<". Error: "<<SDL_GetError()<<"\n";
    }else{
        loaded_textures.push_back(tex);
    }
    return tex;
}

TTF_Font* render_window::load_font(string p_filepath, int size){
    TTF_Font* retval=TTF_OpenFont(p_filepath.c_str(), size);
    if(retval==NULL){
        cerr<<"Error while loading font "<<p_filepath<<". Error: "<<SDL_GetError()<<"\n";
    }else{
        loaded_fonts.push_back(retval);
    }
    return retval;
}

Mix_Chunk* render_window::load_sound(string p_filepath){
    Mix_Chunk* snd=Mix_LoadWAV(p_filepath.c_str());
    if(snd==NULL){
        cerr<<"Error while loading sound "<<p_filepath<<". Error: "<<SDL_GetError()<<"\n";
    }else{
        loaded_sounds.push_back(snd);
    }
    return snd;
}

void render_window::clear(){
    SDL_RenderClear(renderer);
}

void render_window::clear(SDL_Color p_bgcolor){
    SDL_SetRenderDrawColor(renderer, p_bgcolor.r, p_bgcolor.g, p_bgcolor.b, p_bgcolor.a);
    SDL_RenderClear(renderer);
}

void render_window::render_texture(SDL_Texture* p_tex, int p_x, int p_y){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=src.w;
    dst.h=src.h;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void render_window::render_texture_ex(SDL_Texture* p_tex, int p_x, int p_y, float scale){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=src.w*scale;
    dst.h=src.h*scale;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void render_window::render_texture_ex2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=p_w;
    dst.h=p_h;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void render_window::render_texture_pro(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=w*scale;
    dst.h=h*scale;

    SDL_Point center={w/2, h/2};
    //SDL_RenderCopy(renderer, p_tex, &src, &dst);
    SDL_RenderCopyEx(renderer, p_tex, &src, &dst, rotation, &center, SDL_FLIP_NONE);
}

void render_window::render_texture_ultra(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation, SDL_Point rot_center){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=w*scale;
    dst.h=h*scale;

    //SDL_Point center={w/2, h/2};
    //SDL_RenderCopy(renderer, p_tex, &src, &dst);
    SDL_RenderCopyEx(renderer, p_tex, &src, &dst, rotation, &rot_center, SDL_FLIP_NONE);
}

void render_window::render_texture_ultra2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h, float scale, float rotation, SDL_Point rot_center){
    SDL_Rect src;
    SDL_Rect dst;
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    src.x=0;
    src.y=0;
    src.w=w;
    src.h=h;

    dst.x=p_x;
    dst.y=p_y;
    dst.w=p_w*scale;
    dst.h=p_h*scale;

    //SDL_Point center={w/2, h/2};
    //SDL_RenderCopy(renderer, p_tex, &src, &dst);
    SDL_RenderCopyEx(renderer, p_tex, &src, &dst, rotation, &rot_center, SDL_FLIP_NONE);
}

void render_window::display(){
    SDL_RenderPresent(renderer);
}

void render_window::render_entity(entity& p_ent){
    render_texture_ultra2(p_ent.get_tex(), p_ent.get_x(), p_ent.get_y(), p_ent.get_w(), p_ent.get_h(), p_ent.get_scale(), p_ent.get_rotation(), p_ent.get_rot_center());
}

void render_window::render_text(TTF_Font* font, string text, SDL_Color color, int destx, int desty){
    SDL_Surface* tmp_surface=TTF_RenderText_Solid_Wrapped(font, text.c_str(), color,0);
    SDL_Texture* tmp_tex(SDL_CreateTextureFromSurface(renderer, tmp_surface));
    
    render_texture(tmp_tex, destx, desty);

    SDL_FreeSurface(tmp_surface);
    SDL_DestroyTexture(tmp_tex);
}

void render_window::render_text_ex(TTF_Font* font, string text, SDL_Color color, int destx, int desty, float scale){
    SDL_Surface* tmp_surface=TTF_RenderText_Solid_Wrapped(font, text.c_str(), color,0);
    SDL_Texture* tmp_tex(SDL_CreateTextureFromSurface(renderer, tmp_surface));
    
    render_texture_ex(tmp_tex, destx, desty, scale);

    SDL_FreeSurface(tmp_surface);
    SDL_DestroyTexture(tmp_tex);
}

void render_window::render_text_fc(fontcache& p_fc, string text, int destx, int desty){
    int i=0, tempx=destx, tempy=desty;
    while(text[i]!='\0'){
        if(text[i]=='\n'){
            tempx=destx;
            tempy+=get_texture_height(p_fc.get_char_texture('A'))*1.045;
        }else{
            render_texture(p_fc.get_char_texture(text[i]), tempx, tempy);
            tempx+=get_texture_width(p_fc.get_char_texture(text[i]));
        }
        i++;
    }
}

void render_window::render_text_fc_ex(fontcache& p_fc, string text, int destx, int desty, float scale){
    int i=0, tempx=destx, tempy=desty;
    while(text[i]!='\0'){
        if(text[i]=='\n'){
            tempx=destx;
            tempy+=get_texture_height(p_fc.get_char_texture('\n'))*1.045;
        }else{
            render_texture_ex(p_fc.get_char_texture(text[i]), tempx, tempy, scale);
            tempx+=get_texture_width(p_fc.get_char_texture(text[i]));
        }
        i++;
    }
}

void render_window::play_sound(Mix_Chunk* p_sound){
    Mix_PlayChannel(-1, p_sound, 0);
}

void render_window::play_sound_ex(Mix_Chunk* p_sound, int p_times){
    Mix_PlayChannel(-1, p_sound, p_times);
}

void render_window::play_sound_pro(int p_channel, Mix_Chunk* p_sound, int p_times){
    Mix_PlayChannel(p_channel, p_sound, p_times);
}
