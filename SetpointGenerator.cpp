#include "SetpointGenerator.h"

ConstantSignal::ConstantSignal(double value)
{
    this->value = value;
}
double ConstantSignal::generateSignal(int time) //override
{
    return value;
}

SinusoidSignal::SinusoidSignal(double amplitude, double period)
{
    this->amplitude = amplitude;
    this->period = period;
}
double SinusoidSignal::generateSignal(int time) //override
{
    if (this->amplitude == 0 || this->period == 0)
        return 0;
    return amplitude * sin(2 * M_PI / period * time);
}

SquareSignal::SquareSignal(double amplitude, double period, double dutyCycle)
{
    this->amplitude = amplitude;
    this->period = period;
    this->dutyCycle = dutyCycle;
}
double SquareSignal::generateSignal(int time) //override
{
    double t = fmod(time, period);
    double high_time = period * dutyCycle;
    if (t < high_time)
        return amplitude;
    else
        return 0.0;
}

void SetpointGenerator::setStrategy(SignalStrategy *strategy)
{
    this->strategy = strategy;
}
double SetpointGenerator::generate(int time) const
{
    if (strategy != nullptr)
        return strategy->generateSignal(time);

    throw std::runtime_error("No strategy set for the generator");
}
