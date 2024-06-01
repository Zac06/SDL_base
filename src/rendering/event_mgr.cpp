#include "rendering/event_mgr.hpp"

event_mgr::event_mgr(){
    sort(event_container.begin(), event_container.end());
    sort(curr_pressed_keys.begin(), curr_pressed_keys.end());
    update();
    to_clear.clear();
}

int event_mgr::get_event_container_pos(int p_event_type){
    int i=0,c,f=event_container.size()-1;

    while(i<=f){
        c=(i+f)/2;
        if(event_container[c].event_type==p_event_type){
            return c;
        }
        if(event_container[c].event_type<p_event_type){
            i=c+1;
        }else{
            f=c-1;
        }
    }

    return -1;
}

int event_mgr::get_curr_pressed_keys_pos(int p_vkeycode){
    int i=0,c,f=curr_pressed_keys.size()-1;

    while(i<=f){
        c=(i+f)/2;
        if(curr_pressed_keys[c].keysym==p_vkeycode){
            return c;
        }
        if(curr_pressed_keys[c].keysym<p_vkeycode){
            i=c+1;
        }else{
            f=c-1;
        }
    }

    return -1;
}

void event_mgr::manage_keypress(int p_ev_cont_pos){
    int pos=get_curr_pressed_keys_pos(event_container[p_ev_cont_pos].event.key.keysym.sym);

    if(event_container[p_ev_cont_pos].event_type==SDL_KEYDOWN){
        curr_pressed_keys[pos].pressed=true;
    }else if(event_container[p_ev_cont_pos].event_type==SDL_KEYUP){
        curr_pressed_keys[pos].pressed=false;
    }
}

void event_mgr::update(){
    for(list<int>::iterator it=to_clear.begin(); it!=to_clear.end(); it++){
        event_container[*it].status=false;
        event_container[*it].event=SDL_Event();
    }
    to_clear.clear();

    while(SDL_PollEvent(&event)){
        int pos=get_event_container_pos(event.type);

        event_container[pos].status=true;
        event_container[pos].event=event;

        to_clear.push_back(pos);

        if(event.type==SDL_KEYUP||event.type==SDL_KEYDOWN){
            manage_keypress(pos);
        }
    }
}

ev_ret_type event_mgr::get_event(int p_event_id){
    int pos=get_event_container_pos(p_event_id);
    
    if(event_container[pos].status==false){
        return {false, event_container[0].event};
    }
    
    return {true, event_container[pos].event};
}

bool event_mgr::iskeypress(int p_vkeycode){
    return curr_pressed_keys[get_curr_pressed_keys_pos(p_vkeycode)].pressed;
}