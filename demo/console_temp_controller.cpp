#include "console_temp_controller.h"

#include <iostream>

ConsoleTempController::ConsoleTempController()
{
    this->status = stopped;
}

void ConsoleTempController::start_heating()
{
    std::cout << "start_heating" << std::endl;
    this->status = heating;
}

void ConsoleTempController::start_cooling()
{
    std::cout << "start_cooling" << std::endl;
    this->status = cooling;
}

void ConsoleTempController::stop()
{
    std::cout << "stop" << std::endl;
    this->status = stopped;
}
