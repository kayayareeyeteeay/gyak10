#include "application.hpp"
#include "graphics.hpp"

using namespace genv;

application::application(int w, int h) : _width(w), _height(h), focus(-1) {

}

application::~application() {
    for (Widget* w : widgets) delete w;
}

void application::register_widget(Widget* w) {
    widgets.push_back(w);
}

void application::event_loop() {
    gout.open(_width, _height);
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            focus = -1;
            for (size_t i = 0; i < widgets.size(); i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }
        }

        if (ev.type == ev_key && ev.keycode == key_enter) {
            save_action();
        }

        if (focus != -1) {
            widgets[focus]->handle(ev);
        }




        gout << move_to(0,0) << color(0,0,0) << box(_width, _height);

        for (Widget* w : widgets) {
            w->draw();
        }

        gout << move_to(10, _height - 20) << color(255,255,255)
             << text("Karita Arpad Ferenc - PZ7GGI - Fajlbamentes: ENTER (mentes.txt)");

        gout << refresh;
    }
}