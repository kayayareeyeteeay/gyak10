#ifndef NUMERICWIDGET_HPP
#define NUMERICWIDGET_HPP

#include "Widget.hpp"

class NumericWidget : public Widget {
    int _value, _min, _max;
    int _btn_w;
public:
    NumericWidget(application* p, int x, int y, int sx, int sy, int mi, int ma);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual int get_num_value() const override { return _value; }
};

#endif