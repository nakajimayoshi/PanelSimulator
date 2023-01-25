#ifndef UNTITLED1_PANELMANAGER_H
#define UNTITLED1_PANELMANAGER_H

#endif //UNTITLED1_PANELMANAGER_H


#include <deque>
#include <iostream>
#include "Control.h"
#include "string"

class PanelManager {
private:
    int selectedPanel = 1;



public:
    PanelManager() = default;
    ~PanelManager() = default;

    auto print(Control& control) -> std::string {
        switch (control.name) {
            case AUX_PFD:
                return "AUX_PFD" + std::to_string(aux_pfd.getData());
            case PFD:
                return "PFD" + std::to_string(pfd.getData());
            case HALF_PFD:
                return "HALF_PFD" + std::to_string(pfd_half.getData());
            case EICAS:
                return "EICAS" + std::to_string(eicas.getData());
            case ND:
                return "ND" + std::to_string(nd.getData());
            case HALF_ND:
                return "HALF_ND" + std::to_string(nd_half.getData());
            case SYS:
                return "SYS" + std::to_string(sys.getData());
            case CDU:
                return "CDU" + std::to_string(cdu.getData());
            case INFO:
                return "INFO" + std::to_string(info.getData());
            case CHKL:
                return "CHKL" + std::to_string(chkl.getData());
            case COMM:
                return "COMM" + std::to_string(comm.getData());
            default:
                return "display failure";
        }
    };

    Control pfd = Control(PFD, 1);
    Control nd = Control(ND, 2);
    Control pfd_half = Control(HALF_PFD, 3);
    Control nd_half = Control(HALF_ND, 4);
    Control aux_pfd = Control(AUX_PFD, 5);
    Control cdu = Control(CDU, 6);
    Control sys = Control(SYS, 7);
    Control chkl = Control(CHKL, 8);
    Control comm = Control(COMM, 9);
    Control eicas = Control(EICAS, 10);
    Control info = Control(INFO, 11);

    std::deque<Control> masterControls[5] = {
            {aux_pfd, pfd},
            {nd_half, eicas},
            {cdu, cdu},
            {nd},
            {pfd, aux_pfd}
    };

    std::deque<Control> leftIOurBoardDisplay = masterControls[0];
    std::deque<Control> leftInboardDisplay = masterControls[1];
    std::deque<Control> centerDisplay = masterControls[2];
    std::deque<Control> rightInboardDisplay = masterControls[3];
    std::deque<Control> rightOutBoardDisplay = masterControls[4];

    void selectLPanel();
    void selectRPanel();
    std::string test();
    void switchEICAS();
    void selectPage(Control control);

};

void PanelManager::switchEICAS() {

    if(rightInboardDisplay[0].name == ND && leftInboardDisplay[0].name == HALF_ND) {
        this->rightInboardDisplay.pop_back();
        this->rightInboardDisplay.push_back(eicas);
        this->rightInboardDisplay.push_back(nd_half);
        this->leftInboardDisplay.clear();
        this->leftInboardDisplay.push_back(nd);
    }

    if(leftInboardDisplay[1].name == ND && rightInboardDisplay[0].name == HALF_ND) {
        this->leftInboardDisplay.pop_back();
        this->leftInboardDisplay.push_back(nd_half);
        this->leftInboardDisplay.push_back(eicas);
        this->rightInboardDisplay.clear();
        this->rightInboardDisplay.push_back(nd);
    }

    if(this->leftInboardDisplay.size() == 2 && this->rightInboardDisplay.size() == 2) {
          if(this->rightInboardDisplay[0].name == EICAS) {
              this->rightInboardDisplay.pop_front();
              this->rightInboardDisplay.emplace_front(leftInboardDisplay[1]);
              this->leftInboardDisplay.pop_back();
              this->leftInboardDisplay.push_back(eicas);
          }

        if(this->leftInboardDisplay[0].name == EICAS) {
            this->leftInboardDisplay.pop_front();
            this->leftInboardDisplay.emplace_front(rightInboardDisplay[0]);
            this->leftInboardDisplay.pop_back();
            this->leftInboardDisplay.push_back(eicas);
        }
    };
}

std::string PanelManager::test() {
    std::string result = "";
    for(auto & masterControl : masterControls) {
        result.append("--[[");
        result.append("{");
        for(auto & j : masterControl) {
            result += print(j) + "}{";
        }
        result.pop_back();
        result.append("]]--");
    }
    for(int i = 0; i < 2; i++) {
        result.pop_back();
        result.pop_back();
        std::reverse(result.begin(), result.end());
    };

    return result;
}
