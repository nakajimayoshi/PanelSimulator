#include <gtest/gtest.h>
#include "PanelManager.h"

TEST(Base_case, default_state_data_reachable_and_unique) {
    PanelManager p;
    ASSERT_EQ(p.pfd->getData(), 1);
    ASSERT_EQ(p.nd->getData(), 2);
    ASSERT_EQ(p.pfd_half->getData(), 3);
    ASSERT_EQ(p.nd_half->getData(), 4);
    ASSERT_EQ(p.aux_pfd->getData(), 5);
    ASSERT_EQ(p.cdu->getData(), 6);
    ASSERT_EQ(p.sys->getData(), 7);
    ASSERT_EQ(p.chkl->getData(), 8);
    ASSERT_EQ(p.comm->getData(), 9);
    ASSERT_EQ(p.eicas->getData(), 10);
    ASSERT_EQ(p.info->getData(), 11);
}

TEST(setData, setData_works_as_intended) {
    PanelManager p;
    p.pfd->setData(1);
    ASSERT_EQ(p.pfd->getData(), 2);

    p.nd->setData(1);
    ASSERT_EQ(p.nd->getData(), 3);

    p.pfd_half->setData(1);
    ASSERT_EQ(p.pfd_half->getData(), 4);

    p.nd_half->setData(1);
    ASSERT_EQ(p.nd_half->getData(), 5);

    p.aux_pfd->setData(1);
    ASSERT_EQ(p.aux_pfd->getData(), 6);

    p.cdu->setData(1);
    ASSERT_EQ(p.cdu->getData(), 7);

    p.sys->setData(1);
    ASSERT_EQ(p.sys->getData(), 8);

    p.chkl->setData(1);
    ASSERT_EQ(p.chkl->getData(), 9);

    p.comm->setData(1);
    ASSERT_EQ(p.comm->getData(), 10);

    p.eicas->setData(1);
    ASSERT_EQ(p.eicas->getData(), 11);

    p.info->setData(1);
    ASSERT_EQ(p.info->getData(), 12);
}

TEST(PanelManagerPrintMethod, print_method_works_as_intended) {
    PanelManager p;
    ASSERT_EQ(p.print(p.pfd), "PFD1");
    ASSERT_EQ(p.print(p.nd), "ND2");
    ASSERT_EQ(p.print(p.pfd_half), "HALF_PFD3");
    ASSERT_EQ(p.print(p.nd_half), "HALF_ND4");
    ASSERT_EQ(p.print(p.aux_pfd), "AUX_PFD5");
    ASSERT_EQ(p.print(p.cdu), "CDU6");
    ASSERT_EQ(p.print(p.sys), "SYS7");
    ASSERT_EQ(p.print(p.chkl), "CHKL8");
    ASSERT_EQ(p.print(p.comm), "COMM9");
    ASSERT_EQ(p.print(p.eicas), "EICAS10");
    ASSERT_EQ(p.print(p.info), "INFO11");
}

TEST(PanelManagerDefaultMasterControls, Default_Master_test) {
    PanelManager p;
    std::string default_output = "[[{AUX_PFD5}{PFD1}]]----"
                                 "[[{HALF_ND4}{EICAS10}]]----"
                                 "[[{CDU6}{CDU6}]]----"
                                 "[[{ND2}]]----"
                                 "[[{PFD1}{AUX_PFD5}]]";

    ASSERT_EQ(p.log(), default_output);
}

TEST(PanelSelection, select_r_and_l_panels_works) {
    PanelManager p;
    ASSERT_EQ(p.getSelectedPanel(), 1);

    p.selectRPanel();
    ASSERT_EQ(p.getSelectedPanel(), 3);

    p.selectLPanel();
    ASSERT_EQ(p.getSelectedPanel(), 1);
}

TEST(EICASSwitcher, eicas_method_with_half_nd) {
    PanelManager p;
    auto expected_once = "[[{AUX_PFD5}{PFD1}]]----"
                         "[[{ND2}]]----"
                         "[[{CDU6}{CDU6}]]----"
                         "[[{EICAS10}{HALF_ND4}]]----"
                         "[[{PFD1}{AUX_PFD5}]]";

    p.switchEICAS();
    ASSERT_EQ(p.log(), expected_once);


    auto expected_twice = "[[{AUX_PFD5}{PFD1}]]----"
                          "[[{HALF_ND4}{EICAS10}]]----"
                          "[[{CDU6}{CDU6}]]----"
                          "[[{ND2}]]----"
                          "[[{PFD1}{AUX_PFD5}]]";

    p.switchEICAS();
    ASSERT_EQ(p.log(), expected_twice);

    p.switchEICAS();
    ASSERT_EQ(p.log(), expected_once);
}

TEST(SelectPage, select_page_method_works) {
    PanelManager p;

    ASSERT_EQ(p.getSelectedPanel(), 1);

    p.selectPage(p.sys);

    auto expected =  "[[{AUX_PFD5}{PFD1}]]----"
                     "[[{SYS7}{EICAS10}]]----"
                     "[[{CDU6}{CDU6}]]----"
                     "[[{ND2}]]----"
                     "[[{PFD1}{AUX_PFD5}]]";

    ASSERT_EQ(p.log(), expected);

    p.selectPage(p.comm);
    expected = "[[{AUX_PFD5}{PFD1}]]----"
               "[[{COMM9}{EICAS10}]]----"
               "[[{CDU6}{CDU6}]]----"
               "[[{ND2}]]----"
               "[[{PFD1}{AUX_PFD5}]]";

    ASSERT_EQ(p.log(), expected);

    p.switchEICAS();

    expected = "[[{AUX_PFD5}{PFD1}]]----"
               "[[{COMM9}{HALF_ND4}]]----"
               "[[{CDU6}{CDU6}]]----"
               "[[{EICAS10}{HALF_ND4}]]----"
               "[[{PFD1}{AUX_PFD5}]]";

    ASSERT_EQ(p.log(), expected);

}
