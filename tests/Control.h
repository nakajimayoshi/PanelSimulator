#ifndef UNTITLED1_CONTROL_H
#define UNTITLED1_CONTROL_H

#endif //UNTITLED1_CONTROL_H

#include "ControlName.h"
#include "ControlRules.h"

class Control {
private:
    int data;
public:
    Control(ControlName name, int data, ControlRules rules) :
        name(name), data(data), rules(rules) {
        this->name = name;
        this->data = data;
        this->rules = rules;
    }
    ControlName name;
    ControlRules rules;

    [[nodiscard]] auto getData() const -> int;
    auto setData(int x) -> void;

};

auto Control::getData() const -> int {
    return this->data;
}

auto Control::setData(int x) -> void {
    this->data = data + 1;
}

