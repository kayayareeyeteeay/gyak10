#include "SelectorWidget.hpp"
#include "graphics.hpp"
#include "Application.hpp"

using namespace genv;

SelectorWidget::SelectorWidget(application* p, int x, int y, int sx, int sy, std::vector<std::string> opt, int visible)
    : Widget(p, x, y, sx, sy), _options(opt), _selected(0), _opened(false), _scroll_offset(0), _max_visible(visible) {}

void SelectorWidget::draw() {
    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(40,40,40) << box(_size_x-4, _size_y-4);

    if (!_options.empty() && _selected >= 0 && _selected < (int)_options.size()) {
        gout << move_to(_x+10, _y+_size_y/2+5) << color(255,255,255) << text(_options[_selected]);
    }
    gout << move_to(_x+_size_x-20, _y+_size_y/2+5) << color(255,255,255) << text("V");

    if (_opened) {
        for (int i = 0; i < _max_visible && (i + _scroll_offset) < (int)_options.size(); i++) {
            int cur_idx = i + _scroll_offset;
            int cur_y = _y + _size_y + (i * _size_y);
            gout << move_to(_x, cur_y) << color(255,255,255) << box(_size_x, _size_y);
            if (cur_idx == _selected) {
                gout << move_to(_x+1, cur_y+1) << color(100,100,255) << box(_size_x-2, _size_y-2);
            } else {
                gout << move_to(_x+1, cur_y+1) << color(60,60,60) << box(_size_x-2, _size_y-2);
            }
            gout << move_to(_x+5, cur_y+_size_y/2+5) << color(255,255,255) << text(_options[cur_idx]);
        }
    }
}

void SelectorWidget::update_list(std::vector<std::string> new_opt) {
    _options = new_opt;
    if (_selected >= (int)_options.size()) {
        _selected = (int)_options.size() - 1;
    }
    if (_selected < 0 && !_options.empty()) {
        _selected = 0;
    }
    if (_scroll_offset + _max_visible > (int)_options.size()) {
        _scroll_offset = std::max(0, (int)_options.size() - _max_visible);
    }
}

int SelectorWidget::getSelected() const {
    if (_options.empty()) return -1;
    return _selected;
}

std::string SelectorWidget::get_str_value() const {
    if (_options.empty() || _selected < 0) return "";
    return _options[_selected];
}

void SelectorWidget::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (ev.pos_x > _x && ev.pos_x < _x + _size_x && ev.pos_y > _y && ev.pos_y < _y + _size_y) {
            _opened = !_opened;
        }
        else if (_opened) {
            for (int i = 0; i < _max_visible; i++) {
                int elem_y = _y + _size_y + (i * _size_y);
                if (ev.pos_x > _x && ev.pos_x < _x + _size_x && ev.pos_y > elem_y && ev.pos_y < elem_y + _size_y) {
                    int kivalasztott_index = i + _scroll_offset;
                    if (kivalasztott_index < (int)_options.size()) {
                        _selected = kivalasztott_index;
                        _opened = false;
                        _parent->action("enter");
                    }
                }
            }
        }
    }

    if (_opened && ev.type == ev_mouse) {
        if (ev.button == btn_wheelup && _scroll_offset > 0) _scroll_offset--;
        if (ev.button == btn_wheeldown && _scroll_offset + _max_visible < (int)_options.size()) _scroll_offset++;
    }
}

bool SelectorWidget::is_selected(int mx, int my) {
    if (!_opened) {
        return mx > _x && mx < _x + _size_x && my > _y && my < _y + _size_y;
    } else {
        int lathato_elemek = std::min(_max_visible, (int)_options.size());
        int teljes_magassag = _size_y + (lathato_elemek * _size_y);
        return mx > _x && mx < _x + _size_x && my > _y && my < _y + teljes_magassag;
    }
}