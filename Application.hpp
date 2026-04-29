#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Widget.hpp"
#include <vector>
#include <string>

class application {
protected:
    std::vector<Widget*> widgets;
    int focus;
    int _width, _height;
public:
    application(int w, int h);
    virtual ~application();
    void register_widget(Widget* w);
    void event_loop();
    virtual void save_action() = 0;
    virtual void action(std::string id) {}
};

#endif