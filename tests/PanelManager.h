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
                return "AUX_PFD" + std::to_string(aux_pfd.getData()) + subdivider;
            case PFD:
                return "PFD" + std::to_string(pfd.getData()) + subdivider;
            case HALF_PFD:
                return "HALF_PFD" + std::to_string(pfd_half.getData()) + subdivider;
            case EICAS:
                return "EICAS" + std::to_string(eicas.getData()) + subdivider;
            case ND:
                return "ND" + std::to_string(nd.getData()) + subdivider;
            case HALF_ND:
                return "HALF_ND" + std::to_string(nd_half.getData()) + subdivider;
            case SYS:
                return "SYS" + std::to_string(sys.getData()) + subdivider;
            case CDU:
                return "CDU" + std::to_string(cdu.getData()) + subdivider;
            case INFO:
                return "INFO" + std::to_string(info.getData()) + subdivider;
            case CHKL:
                return "CHKL" + std::to_string(chkl.getData()) + subdivider;
            case COMM:
                return "COMM" + std::to_string(comm.getData()) + subdivider;
            default:
                std::cout << "display failure" << subdivider;
        }
    }

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
    for(auto & masterControl : masterControls) {
        for(auto & j : masterControl) {
            return print(j);
        }
    }
}
