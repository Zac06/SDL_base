#include "base_elements/gui_element.hpp"

gui_element::gui_element(SDL_Texture* p_tex_normal, event_mgr& p_events, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_normal), 
    tex_active(p_tex_normal), 
    tex_disabled(p_tex_normal),
    state(0),
    events(p_events)
{
    x=p_coords.x;
    y=p_coords.y;
}

gui_element::gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, event_mgr& p_events, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_normal), 
    tex_active(p_tex_active), 
    tex_disabled(p_tex_normal),
    state(0),
    events(p_events)
{
    x=p_coords.x;
    y=p_coords.y;
}

gui_element::gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, event_mgr& p_events, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_hover), 
    tex_active(p_tex_active), 
    tex_disabled(p_tex_disabled),
    state(0),
    events(p_events)
{
    x=p_coords.x;
    y=p_coords.y;
}

void gui_element::set_state(int p_state){
    state=p_state;
}

int gui_element::get_state(){
    return state;
}