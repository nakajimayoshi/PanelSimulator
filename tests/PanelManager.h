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

    auto print(Control& control) -> std::string {
        const std::string subdivider = "}{";
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

   std::deque<Control> masterControls[5] = {
            {aux_pfd, pfd},
            {nd_half, eicas},
            {cdu, cdu},
            {nd},
            {pfd, aux_pfd}
    };


    void selectLPanel();
    void selectRPanel();
    std::string test();
    void switchEICAS();
    void selectPage(Control control);

};

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
