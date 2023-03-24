#include <memory>

#include <thermostat.hpp>

#include "console_temp_controller.h"

int main()
{
    auto controller = std::make_shared<ConsoleTempController>();
    auto thermostat = std::make_unique<Thermostat<int>>(controller, 21, 23);

    thermostat->updateTemp(19);
    thermostat->updateTemp(20);
    thermostat->updateTemp(21);
    thermostat->updateTemp(22);
    thermostat->updateTemp(23);
    thermostat->updateTemp(24);
    thermostat->updateTemp(23);
    thermostat->updateTemp(22);

    return 0;
}