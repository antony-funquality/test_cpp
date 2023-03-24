#ifndef __thermostat_h_p5a4tax596g9__
#define __thermostat_h_p5a4tax596g9__

#include <memory>
#include <stdexcept>

namespace ThermostatInternal
{
    enum ThermostatStatus
    {
        stopped,
        heating,
        cooling
    };
};

class TempControllerInterface
{
public:
    virtual void start_heating() = 0;
    virtual void start_cooling() = 0;
    virtual void stop() = 0;
};

/**
 * @tparam T Should be any "number" type.
 */
template <typename T>
class Thermostat
{
protected:
    T _minTemp;
    T _maxTemp;
    ThermostatInternal::ThermostatStatus _status;
    std::shared_ptr<TempControllerInterface> _controller;

public:
    Thermostat(std::shared_ptr<TempControllerInterface> controller, T minTemp, T maxTemp);
    void updateTemp(T currentTemp);
};

template <typename T>
Thermostat<T>::Thermostat(std::shared_ptr<TempControllerInterface> controller, T minTemp, T maxTemp)
{
    if (!(maxTemp > minTemp))
    {
        throw std::invalid_argument("Max must be higher than min.");
    }

    this->_controller = controller;

    this->_minTemp = minTemp;
    this->_maxTemp = maxTemp;
}

template <typename T>
void Thermostat<T>::updateTemp(T currentTemp)
{
    if (currentTemp < this->_minTemp)
    {
        if (this->_status != ThermostatInternal::ThermostatStatus::heating)
        {
            this->_controller->start_heating();
            this->_status = ThermostatInternal::ThermostatStatus::heating;
        }
    }
    else if (currentTemp > this->_maxTemp)
    {
        if (this->_status != ThermostatInternal::ThermostatStatus::cooling)
        {
            this->_controller->start_cooling();
            this->_status = ThermostatInternal::ThermostatStatus::cooling;
        }
    }
    else
    {
        if (this->_status != ThermostatInternal::ThermostatStatus::stopped)
        {
            this->_controller->stop();
            this->_status = ThermostatInternal::ThermostatStatus::stopped;
        }
    }
}

#endif
