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
class MyApp : public application {

    class Button: public Widget {
    public:
        Button(application *parent,
           int x, int y, int sx, int sy, std::string lab)
       Widget(parent, x,y,sx,sy),
       _label(lab){}
        void draw() const override {
            gout<<move_to(_x,_y)<<color(255,255,255)<<box(_x,_y);
            gout<<move_to(_x)
        }
    protected:
        string _label

    }

public:
    MyApp(int width, int height):application(width,height)
    {
        new NumericWidget(this, 50, 50, 150, 40, 0, 100);
        new NumericWidget(this, 50, 110, 150, 40, -50, 50);

        s1 = {"Alma", "Korte", "Szilva", "Barack", "Meggy"};
        s2 = {"C++", "Java", "Python", "Rust", "Go", "C#", "Swift"};

        mn1 = new SelectorWidget(this, 300, 50, 150, 40, s1, 3);
        mn2 = new SelectorWidget(this, 300, 250, 150, 40, s2, 4);
    }

    void action(string id) {
        if (id == "enter") {
            kiesik();
        }
    }

    void kiesik() {
        int ind = mn1->getSelected();
        if (ind >= 0 && ind < (int)s1.size()) {
            s2.push_back(s1[ind]);
            s1.erase(s1.begin() + ind);

            mn1->update_list(s1);
            mn2->update_list(s2);
        }
    }

protected:
    SelectorWidget *mn1, *mn2;
    vector<string> s1, s2;

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