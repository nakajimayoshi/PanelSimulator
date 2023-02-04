#ifndef UNTITLED1_PANELMANAGER_H
#define UNTITLED1_PANELMANAGER_H

#endif //UNTITLED1_PANELMANAGER_H

// FCOM 10.20.2
// Multiple display instances managed in 3 ways:
// Synchronized (Changes on one affect the other)
// Independent (no linkage of state)
// Blank (when max allowed instances is exceeded, display becomes blank with "Select MFD"

#include <deque>
#include <iostream>
#include "Control.h"
#include "string"
#include <unordered_map>
#include "ControlSelection.h"

class PanelManager {
private:
    ControlSelection captSelectedControl = LEFT;
    ControlSelection foSelectedControl = RIGHT;
    std::shared_ptr<Control> captStoredControl = null_control;
    std::shared_ptr<Control> foStoredControl = null_control;

public:
    PanelManager() = default;
    ~PanelManager() = default;

    auto print(std::shared_ptr<Control>& control) -> std::string {
        switch (control->name) {
            case AUX_PFD:
                return "AUX_PFD" + std::to_string(aux_pfd->getData());
            case PFD:
                return "PFD" + std::to_string(pfd->getData());
            case HALF_PFD:
                return "HALF_PFD" + std::to_string(pfd_half->getData());
            case EICAS:
                return "EICAS" + std::to_string(eicas->getData());
            case ND:
                return "ND" + std::to_string(nd->getData());
            case HALF_ND:
                return "HALF_ND" + std::to_string(nd_half->getData());
            case SYS:
                return "SYS" + std::to_string(sys->getData());
            case CDU:
                return "CDU" + std::to_string(cdu->getData());
            case INFO:
                return "INFO" + std::to_string(info->getData());
            case CHKL:
                return "CHKL" + std::to_string(chkl->getData());
            case COMM:
                return "COMM" + std::to_string(comm->getData());
            case SELECT_MFD:
                return "SELECT MFD" + std::to_string(blank->getData());
            case NULLCTRL:
                return "NULL CONTROL" + std::to_string(null_control->getData());
            default:
                return "display failure";
        }
    };

    std::shared_ptr<Control> pfd = std::make_shared<Control>(PFD, 1, SYNCHRONOUS);
    std::shared_ptr<Control> nd = std::make_shared<Control>(ND, 2, INDEPENDENT);
    std::shared_ptr<Control> pfd_half = std::make_shared<Control>(HALF_PFD, 3, SYNCHRONOUS);
    std::shared_ptr<Control> nd_half = std::make_shared<Control>(HALF_ND, 4, INDEPENDENT);
    std::shared_ptr<Control> aux_pfd = std::make_shared<Control>(AUX_PFD, 5, SYNCHRONOUS);
    std::shared_ptr<Control> cdu = std::make_shared<Control>(CDU, 6, INDEPENDENT);
    std::shared_ptr<Control> sys = std::make_shared<Control>(SYS, 7, INDEPENDENT);
    std::shared_ptr<Control> chkl = std::make_shared<Control>(CHKL, 8, SYNCHRONOUS);
    std::shared_ptr<Control> comm = std::make_shared<Control>(COMM, 9, INDEPENDENT);
    std::shared_ptr<Control> eicas = std::make_shared<Control>(EICAS, 10, SYNCHRONOUS);
    std::shared_ptr<Control> info = std::make_shared<Control>(INFO, 11, INDEPENDENT);
    std::shared_ptr<Control> blank = std::make_shared<Control>(SELECT_MFD, 12, BLANK);
    std::shared_ptr<Control> null_control = std::make_shared<Control>(NULLCTRL, 0, BLANK);

    std::deque<std::shared_ptr<Control>> masterControls[5] = {
            {aux_pfd, pfd},
            {nd_half, eicas},
            {cdu, cdu},
            {null_control, nd},
            {pfd, aux_pfd}
    };

    std::deque<std::shared_ptr<Control>> leftOutboardDisplay = masterControls[0];
    std::deque<std::shared_ptr<Control>> leftInboardDisplay = masterControls[1];
    std::deque<std::shared_ptr<Control>> cduDisplay = masterControls[2];
    std::deque<std::shared_ptr<Control>> rightInboardDisplay = masterControls[3];
    std::deque<std::shared_ptr<Control>> rightOutboardDisplay = masterControls[4];

    void captSelectLControl();
    void captSelectRControl();
    void foSelectLControl();
    void foSelectRControl();
    ControlSelection getCaptSelectedControl();
    ControlSelection getFoSelectedControl();
    std::string log();
    void switchEICAS();
    void captSelectPage(const std::shared_ptr<Control>& control);
    void foSelectPage(const std::shared_ptr<Control>& control);
    void captSelectCDUPage(const std::shared_ptr<Control>& control);
    void foSelectCDUPage(const std::shared_ptr<Control>& control);

};

void PanelManager::switchEICAS() {

};

void PanelManager::captSelectPage(const std::shared_ptr<Control>& control) {


    switch(captSelectedControl) {
        case 0:
            leftInboardDisplay.pop_front();
            leftInboardDisplay.push_front(control);

        case 1:
            if(leftInboardDisplay[captSelectedControl]->name == EICAS) {

            }
    };

}

void PanelManager::captSelectCDUPage(const std::shared_ptr<Control>& control) {

}

void PanelManager::captSelectLControl() {
        this->captSelectedControl = LEFT;
}

void PanelManager::captSelectRControl() {
    if(leftInboardDisplay.back()->name == EICAS) {
        throw std::runtime_error("error: EICAS occupies selected control");
    } else {
        this->captSelectedControl = RIGHT;
    }
}

ControlSelection PanelManager::getCaptSelectedControl() {
    return this->captSelectedControl;
}

void PanelManager::foSelectLControl() {
    if(rightInboardDisplay.front()->name != EICAS) {
        this->foSelectedControl = LEFT;
    } else {
        throw std::runtime_error("error: EICAS occupies selected control");
        }
}

void PanelManager::foSelectRControl() {
    this->foSelectedControl = RIGHT;
}

ControlSelection PanelManager::getFoSelectedControl() {
    return this->foSelectedControl;
}

std::string PanelManager::log() {
    std::string result;
    auto& panels = reinterpret_cast<const std::array<std::deque<std::shared_ptr<Control>>, 5> &>(masterControls);
    for(const auto & panel : panels) {
        result.append("--[[");
        result.append("{");
        for(auto& j : panel) {
            result += print(const_cast<std::shared_ptr<Control> &>(j)) + "}{";
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
