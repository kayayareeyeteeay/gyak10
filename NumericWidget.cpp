#include "NumericWidget.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;

NumericWidget::NumericWidget(application* p, int x, int y, int sx, int sy, int mi, int ma) 
    : Widget(p, x, y, sx, sy), _min(mi), _max(ma), _value(mi), _btn_w(30) {}

void NumericWidget::draw() {

    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    

    gout << move_to(_x + 10, _y + _size_y/2 + 5) << color(255,255,255) << text(std::to_string(_value));
    

    gout << move_to(_x + _size_x - _btn_w, _y) << color(100,100,100) << box(_btn_w, _size_y/2);
    gout << move_to(_x + _size_x - _btn_w, _y + _size_y/2) << color(80,80,80) << box(_btn_w, _size_y/2);
    gout << move_to(_x + _size_x - _btn_w + 10, _y + 15) << color(255,255,255) << text("+");
    gout << move_to(_x + _size_x - _btn_w + 10, _y + _size_y/2 + 15) << color(255,255,255) << text("-");
}

void NumericWidget::handle(event ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_up) _value++;
        if (ev.keycode == key_down) _value--;
        if (ev.keycode == key_pgup) _value += 10;
        if (ev.keycode == key_pgdn) _value -= 10;
    }
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (ev.pos_x > _x + _size_x - _btn_w && ev.pos_x < _x + _size_x) {
            if (ev.pos_y > _y && ev.pos_y < _y + _size_y/2) _value++;
            if (ev.pos_y > _y + _size_y/2 && ev.pos_y < _y + _size_y) _value--;
        }
    }
    if (_value < _min) _value = _min;
    if (_value > _max) _value = _max;
}