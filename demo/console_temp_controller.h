#ifndef __console_temp_controller_h_p5a4tax596g9__
#define __console_temp_controller_h_p5a4tax596g9__

#include <thermostat.hpp>

enum ConsoleTempControllerStatus
{
    stopped,
    heating,
    cooling
};

class ConsoleTempController : public TempControllerInterface
{
protected:
    ConsoleTempControllerStatus status;

public:
    ConsoleTempController();
    void start_heating();
    void start_cooling();
    void stop();
};

#endif
