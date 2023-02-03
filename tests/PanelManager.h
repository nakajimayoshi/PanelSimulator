#ifndef UNTITLED1_PANELMANAGER_H
#define UNTITLED1_PANELMANAGER_H

#endif //UNTITLED1_PANELMANAGER_H


#include <deque>
#include <iostream>
#include "Control.h"
#include "string"
#include <unordered_map>

class PanelManager {
private:
    int selectedPanel = 1;

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
            default:
                return "display failure";
        }
    };

    std::shared_ptr<Control> pfd = std::make_shared<Control>(PFD, 1);
    std::shared_ptr<Control> nd = std::make_shared<Control>(ND, 2);
    std::shared_ptr<Control> pfd_half = std::make_shared<Control>(HALF_PFD, 3);
    std::shared_ptr<Control> nd_half = std::make_shared<Control>(HALF_ND, 4);
    std::shared_ptr<Control> aux_pfd = std::make_shared<Control>(AUX_PFD, 5);
    std::shared_ptr<Control> cdu = std::make_shared<Control>(CDU, 6);
    std::shared_ptr<Control> sys = std::make_shared<Control>(SYS, 7);
    std::shared_ptr<Control> chkl = std::make_shared<Control>(CHKL, 8);
    std::shared_ptr<Control> comm = std::make_shared<Control>(COMM, 9);
    std::shared_ptr<Control> eicas = std::make_shared<Control>(EICAS, 10);
    std::shared_ptr<Control> info = std::make_shared<Control>(INFO, 11);

    std::deque<std::shared_ptr<Control>> masterControls[5] = {
            {aux_pfd, pfd},
            {nd_half, eicas},
            {cdu, cdu},
            {nd},
            {pfd, aux_pfd}
    };


    void selectLPanel();
    void selectRPanel();
    int getSelectedPanel();
    std::string log();
    void switchEICAS();
    void selectPage(const std::shared_ptr<Control>& control);
    void selectCDUPage(Control control);

};

void PanelManager::switchEICAS() {
    auto &leftInboardDisplay = masterControls[1];
    auto &rightInboardDisplay = masterControls[3];

    if (leftInboardDisplay.front()->name == ND || rightInboardDisplay.front()->name == ND) {
        if (leftInboardDisplay.front()->name == ND) {
            leftInboardDisplay.clear();
            leftInboardDisplay.push_back(nd_half);
            leftInboardDisplay.push_back(eicas);
            rightInboardDisplay.clear();
            rightInboardDisplay.push_back(nd);
        } else if(rightInboardDisplay.front()->name == ND) {
            rightInboardDisplay.clear();
            rightInboardDisplay.push_back(eicas);
            rightInboardDisplay.push_back(nd_half);
            leftInboardDisplay.clear();
            leftInboardDisplay.push_back(nd);
            }
        } else {
        if(leftInboardDisplay.back()->name == EICAS) {
            leftInboardDisplay.pop_back();
            leftInboardDisplay.push_back(rightInboardDisplay.front());
            rightInboardDisplay.pop_front();
            rightInboardDisplay.push_front(eicas);
        } else {
            rightInboardDisplay.pop_front();
            rightInboardDisplay.push_front(leftInboardDisplay.back());
            leftInboardDisplay.pop_back();
            leftInboardDisplay.push_back(eicas);
        }
    }
}

void PanelManager::selectPage(const std::shared_ptr<Control>& control) {

    auto& leftInboardDisplay = masterControls[1];
    auto& rightInboardDisplay = masterControls[3];

    if(this->selectedPanel == 1 && leftInboardDisplay.front()->name == ND) {
        leftInboardDisplay.pop_front();
        leftInboardDisplay.push_front(nd_half);
        leftInboardDisplay.push_back(control);
    } else if(this->selectedPanel == 1 && leftInboardDisplay.back()->name == EICAS) {
        leftInboardDisplay.pop_front();
        leftInboardDisplay.push_front(control);

    } else if (this->selectedPanel == 3 && rightInboardDisplay.front()->name == ND) {
        rightInboardDisplay.pop_front();
        rightInboardDisplay.push_front(control);
        rightInboardDisplay.push_back(nd_half);
    } else if (this->selectedPanel == 3 && rightInboardDisplay.front()->name == EICAS) {
        rightInboardDisplay.pop_back();
        rightInboardDisplay.push_back(control);
    }
}

void PanelManager::selectCDUPage(Control control) {

}

void PanelManager::selectLPanel() {
    this->selectedPanel = 1;
}

void PanelManager::selectRPanel() {
    this->selectedPanel = 3;
}

int PanelManager::getSelectedPanel() {
    return this->selectedPanel;
}

std::string PanelManager::log() {
    std::string result;
    auto& panels = masterControls;
    for(int i = 0; i < panels->size(); i++) {
        result.append("--[[");
        result.append("{");
        for(int j = 0; j < panels[i].size(); j++) {
            result += print(panels[i][j]) + "}{";
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
