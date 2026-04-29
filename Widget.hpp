#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include <string>

class application;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
    application * _parent;
public:
    Widget(application * p, int x, int y, int sx, int sy);
    virtual ~Widget() {}
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;

    virtual int get_num_value() const { return 0; }
    virtual std::string get_str_value() const { return ""; }
};

#endif