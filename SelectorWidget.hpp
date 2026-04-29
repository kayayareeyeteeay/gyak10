#ifndef SELECTORWIDGET_HPP
#define SELECTORWIDGET_HPP

#include "Widget.hpp"
#include <vector>
#include <string>

class SelectorWidget : public Widget {
    std::vector<std::string> _options;
    int _selected;
    bool _opened;
    int _scroll_offset;
    int _max_visible;
public:
    SelectorWidget(application* p, int x, int y, int sx, int sy, std::vector<std::string> opt, int visible);

    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual bool is_selected(int mouse_x, int mouse_y) override;


    virtual std::string get_str_value() const override;
    int getSelected() const;
    void update_list(std::vector<std::string> new_opt);

};

#endif