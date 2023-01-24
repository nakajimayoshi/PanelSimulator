#include <deque>
#include <iostream>


class Panels {
private:
    int selectedPanel = 1;

public:
    Panels() = default;
    enum Control {
        AUX_PFD,
        PFD,
        HALF_PFD,
        ND,
        HALF_ND,
        EICAS,
        SYS,
        CDU,
        INFO,
        CHKL,
        COMM,
    };

    Control pfd = Control::PFD;
    Control nd = Control::ND;
    Control pfd_half = Control::HALF_PFD;
    Control nd_half = Control::HALF_ND;
    Control aux_pfd = Control::AUX_PFD;
    Control cdu = Control::CDU;
    Control sys = Control::SYS;
    Control chkl = Control::CHKL;
    Control comm = Control::COMM;
    Control eicas = Control::EICAS;
    Control info = Control::INFO;

    auto print(Control& control) -> void {
        switch (control) {
            case AUX_PFD:
                std::cout << "AUX_PFD" << "----";
                break;
            case PFD:
                std::cout << "PFD" << "----";
                break;
            case HALF_PFD:
                std::cout << "HALF_PFD" << "----";
                break;
            case EICAS:
                std::cout << "EICAS" << "----";
                break;
            case ND:
                std::cout << "ND" << "----";
                break;
            case HALF_ND:
                std::cout << "HALF_ND" << "----";
                 break;
            case SYS:
                std::cout << "SYS" << "----";
                break;
            case CDU:
                std::cout << "CDU" << "----";
                break;
            case INFO:
                std::cout << "INFO" << "----";
                break;
            case CHKL:
                std::cout << "CHKL" << "----";
                break;
            case COMM:
                std::cout << "COMM" << "----";
                break;
            default:
                std::cout << "display failure" << "----";
                break;
        }
    }

    [[maybe_unused]] std::deque<Control> godPanel[5] = {
            {aux_pfd, pfd},
            {nd_half, eicas},
            {cdu, cdu},
            {nd},
            {pfd, aux_pfd}
    };


    void selectLPanel();
    void selectRPanel();
    void test();
    void switchEICAS();
    void selectPage(Control control);

};

void Panels::test() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < godPanel[i].size(); j++) {
            print(godPanel[i][j]);
        }
    }
    std::cout << "" << std::endl;
};

void Panels::selectLPanel() {
    this->selectedPanel = 1;

    std::cout << "Selected Panel is now: " << this->selectedPanel << std::endl;
};

void Panels::selectRPanel() {
    this->selectedPanel = 3;

    std::cout << "Selected Panel is now: " << this->selectedPanel << std::endl;
};

void Panels::switchEICAS() {

    if(godPanel[1][1] == eicas) {
        godPanel[3].emplace_front(godPanel[1][1]);
        godPanel[3].pop_back();
        godPanel[1].clear();
        godPanel[1].push_back(nd);
        godPanel[3].push_back(nd_half);
    }
    else if(godPanel[3][1] != eicas) {
        godPanel[1].emplace_front(godPanel[3][1]);
        godPanel[1].pop_back();
        godPanel[1].push_back(eicas);
        godPanel[3].clear();
        godPanel[3].push_back(nd);
    }

}

void Panels::selectPage(Control control) {
    if(this->selectedPanel == 1) {
        if(this->godPanel[this->selectedPanel].size() == 1) {
            godPanel[1].pop_back();
            godPanel[1].push_back(nd_half);
            godPanel[1].push_back(control);
        };

        if(this->godPanel[this->selectedPanel].size() == 2) {
            godPanel[1].pop_back();
            godPanel[1].emplace_front(control);
        }
    }

    if(this->selectedPanel == 3) {
        if(this->godPanel[this->selectedPanel].size() == 1) {
            godPanel[3].pop_back();
            godPanel[3].push_back(nd_half);
            godPanel[3].push_back(control);
        };

        if(this->godPanel[this->selectedPanel].size() == 2) {
            godPanel[3].pop_back();
            godPanel[3].push_back(control);
        }

    }
};

int main() {

    std::cout << "Hello" << std::endl;

};