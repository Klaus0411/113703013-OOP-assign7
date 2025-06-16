#include <iostream>
#include <string>
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"

/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << std::endl << std::endl;
}



int main(){

    View view;
    Controller controller(view);
    controller.run();
    PrintMyID("113703013");
}
