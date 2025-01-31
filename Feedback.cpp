#include "Feedback.h"

void Feedback::setGeneratedValue(double generatedValue)
{
    this->generatedValue = generatedValue;
}
void Feedback::setMeasuredValue(double measuredValue)
{
    this->measuredValue = measuredValue;
}
double Feedback::getError()
{
    return this->generatedValue - this->measuredValue;
}

void Feedback::reset()
{
    double measuredValue = 0;
    double generatedValue = 0;
}
