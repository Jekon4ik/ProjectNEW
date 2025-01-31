#include "PIDRegulator.h"

double PID::calculateProportional()
{
    return this->k * this->error;
}
double PID::calculateIntegral()
{
    if (this->Ti == 0)
        return 0;
    this->errorSum += this->error;
    return this->errorSum / this->Ti;
}
double PID::calculateDerivative()
{
    return this->Td * (this->error - this->previosError);
}

PID::PID(double k)
{
    this->k = k;
    this->Ti = 0;
    this->Td = 0;
}
PID::PID(double k, double Ti)
{
    this->k = k;
    this->Ti = Ti;
    this->Td = 0;
}
PID::PID(double k, double Ti, double Td)
{
    this->k = k;
    this->Ti = Ti;
    this->Td = Td;
}
void PID::setK(double k)
{
    this->k = k;
}
void PID::setTi(double Ti)
{
    this->Ti = Ti;
}
void PID::setTd(double Td)
{
    this->Td = Td;
}
void PID::setError(double error)
{
    this->previosError = this->error;
    this->error = error;
}

double PID::getControlledValue(double error)
{
    setError(error);
    this->lastControlValue = calculateProportional() + calculateIntegral()
                             + calculateDerivative(); //wstepnie
    return lastControlValue;
}

double PID::getLastControllValue() const
{
    return this->lastControlValue;
}
