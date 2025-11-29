#include <iostream>
#include "controller.h"

int main() {
    std::cout << "Starting app.." << std::endl;
    Controller controller;
    controller.activate();
    controller.processTask(42);
    controller.deactivate();
    std::cout << "App finished." << std::endl;
    return 0;
}