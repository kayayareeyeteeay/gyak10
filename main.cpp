#include "application.hpp"
#include "NumericWidget.hpp"
#include "SelectorWidget.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
using namespace genv;

// Egy általános nyomógomb osztály
class Button : public Widget {
    string _label;
    string _action_id;
    int _trigger_key;
public:
    Button(application *parent, int x, int y, int sx, int sy, string lab, string id, int key)
        : Widget(parent, x, y, sx, sy), _label(lab), _action_id(id), _trigger_key(key) {}

    void draw() override {
        // Keret és háttér
        gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
        gout << move_to(_x + 2, _y + 2) << color(100, 100, 100) << box(_size_x - 4, _size_y - 4);

        // Szöveg középre igazítása (egyszerűsítve)
        int text_w = gout.twidth(_label);
        gout << move_to(_x + (_size_x - text_w) / 2, _y + _size_y / 2 + 5)
             << color(255, 255, 255) << text(_label);
    }

    void handle(event ev) override {
        // Ha bal egérrel rákattintanak, vagy megnyomják a dedikált gombot
        if ((ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) ||
            (ev.type == ev_key && ev.keycode == _trigger_key)) {
            _parent->action(_action_id);
        }
    }
};

class MyApp : public application {
protected:
    SelectorWidget *mn1, *mn2;
    vector<string> s1, s2;
    Button *btn_right, *btn_left;

public:
    MyApp(int width, int height) : application(width, height) {
        new NumericWidget(this, 50, 50, 150, 40, 0, 100);
        new NumericWidget(this, 50, 110, 150, 40, -50, 50);

        s1 = {"Alma", "Korte", "Szilva", "Barack", "Meggy"};
        s2 = {"C++", "Java", "Python", "Rust", "Go", "C#", "Swift"};

        mn1 = new SelectorWidget(this, 300, 50, 150, 40, s1, 3);
        mn2 = new SelectorWidget(this, 300, 250, 150, 40, s2, 4);


        btn_right = new Button(this, 300, 200, 150, 40, "Atvisz (Enter)", "jobbra", key_enter);


        btn_left = new Button(this, 300, 450, 150, 40, "Visszahoz (Space)", "balra", key_space);
    }

    void action(string id) override {
        if (id == "jobbra") {
            atvisz();
        }
        if (id == "balra") {
            visszatesz();
        }

        if (id == "enter") {
            atvisz();
        }
    }


    void atvisz() {
        int ind = mn1->getSelected();
        if (ind >= 0 && ind < (int)s1.size()) {
            s2.push_back(s1[ind]);
            s1.erase(s1.begin() + ind);
            mn1->update_list(s1);
            mn2->update_list(s2);
        }
    }


    void visszatesz() {
        int ind = mn2->getSelected();
        if (ind >= 0 && ind < (int)s2.size()) {
            s1.push_back(s2[ind]);
            s2.erase(s2.begin() + ind);
            mn1->update_list(s1);
            mn2->update_list(s2);
        }
    }

    void save_action() override {
        ofstream f("mentes.txt");
        for (Widget* w : widgets) {
            if (NumericWidget* nw = dynamic_cast<NumericWidget*>(w)) {
                f << "Numeric ertek: " << nw->get_num_value() << endl;
            }
            else if (SelectorWidget* sw = dynamic_cast<SelectorWidget*>(w)) {
                f << "Selector ertek: " << sw->get_str_value() << endl;
            }
        }
        f.close();
    }
};

int main() {
    MyApp app(800, 600);
    app.event_loop();
    return 0;
}