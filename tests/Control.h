#ifndef UNTITLED1_CONTROL_H
#define UNTITLED1_CONTROL_H

#endif //UNTITLED1_CONTROL_H

#include "ControlName.h"

class Control {
private:
    int data;
public:
    Control(ControlName name, int data) :
        name(name), data(data) {
        this->name = name;
        this->data = data;
    }
    ControlName name;

    auto getData() -> int;
    auto setData(int x) -> void;
};

auto Control::getData() -> int {
    return this->data;
}

auto Control::setData(int x) -> void {
    this->data = data + 1;
}