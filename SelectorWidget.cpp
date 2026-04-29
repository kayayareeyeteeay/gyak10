#include "SelectorWidget.hpp"
#include "graphics.hpp"
#include "Application.hpp"
#include <algorithm>

using namespace genv;

SelectorWidget::SelectorWidget(application* p, int x, int y, int sx, int sy, std::vector<std::string> opt, int visible)
    : Widget(p, x, y, sx, sy), _options(opt), _selected(0), _scroll_offset(0), _max_visible(visible) {}

void SelectorWidget::draw() {

    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y * _max_visible);

    for (int i = 0; i < _max_visible && (i + _scroll_offset) < (int)_options.size(); i++) {
        int cur_idx = i + _scroll_offset;
        int cur_y = _y + (i * _size_y);


        if (cur_idx == _selected) {
            gout << move_to(_x + 2, cur_y + 2) << color(100, 100, 255) << box(_size_x - 4, _size_y - 4);
        } else {
            gout << move_to(_x + 2, cur_y + 2) << color(40, 40, 40) << box(_size_x - 4, _size_y - 4);
        }


        gout << move_to(_x + 10, cur_y + _size_y / 2 + 5) << color(255, 255, 255) << text(_options[cur_idx]);
    }
}

void SelectorWidget::handle(event ev) {
    if (ev.type == ev_mouse) {

        if (ev.button == btn_left) {
            for (int i = 0; i < _max_visible; i++) {
                int elem_y = _y + (i * _size_y);
                if (ev.pos_x > _x && ev.pos_x < _x + _size_x && ev.pos_y > elem_y && ev.pos_y < elem_y + _size_y) {
                    int clicked_idx = i + _scroll_offset;
                    if (clicked_idx < (int)_options.size()) {
                        _selected = clicked_idx;
                    }
                }
            }
        }

        if (ev.button == btn_wheelup && _scroll_offset > 0) _scroll_offset--;
        if (ev.button == btn_wheeldown && _scroll_offset + _max_visible < (int)_options.size()) _scroll_offset++;
    }


    if (ev.type == ev_key) {
        if (ev.keycode == key_up && _selected > 0) {
            _selected--;
            if (_selected < _scroll_offset) _scroll_offset = _selected;
        }
        if (ev.keycode == key_down && _selected < (int)_options.size() - 1) {
            _selected++;
            if (_selected >= _scroll_offset + _max_visible) _scroll_offset = _selected - _max_visible + 1;
        }
    }
}

bool SelectorWidget::is_selected(int mx, int my) {

    return mx > _x && mx < _x + _size_x && my > _y && my < _y + (_size_y * _max_visible);
}

void SelectorWidget::update_list(std::vector<std::string> new_opt) {
    _options = new_opt;
    if (_selected >= (int)_options.size()) {
        _selected = std::max(-1, (int)_options.size() - 1);
    }
    if (_selected < 0 && !_options.empty()) {
        _selected = 0;
    }
    if (_scroll_offset + _max_visible > (int)_options.size()) {
        _scroll_offset = std::max(0, (int)_options.size() - _max_visible);
    }
}

int SelectorWidget::getSelected() const {
    return _selected;
}

std::string SelectorWidget::get_str_value() const {
    if (_options.empty() || _selected < 0 || _selected >= (int)_options.size()) return "";
    return _options[_selected];
}