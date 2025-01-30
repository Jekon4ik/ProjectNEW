#include "ARX.h"

Arx::Arx(const vector<double> &a, const vector<double> &b, int k)
{
    this->a = a;
    this->b = b;
    this->k = k;

    adjustedValuesBuffer.resize(a.size(), 0.0);
    controlValuesBuffer.resize(k + b.size(), 0.0);
}
void Arx::addControlValue(double controlValue)
{
    for (int i = controlValuesBuffer.size() - 1; i > 0; i--) {
        controlValuesBuffer[i] = controlValuesBuffer[i - 1];
    }
    controlValuesBuffer[0] = controlValue;
}

void Arx::addAdjustedValue(double adjustedValue)
{
    for (int i = adjustedValuesBuffer.size() - 1; i > 0; i--) {
        adjustedValuesBuffer[i] = adjustedValuesBuffer[i - 1];
    }
    adjustedValuesBuffer[0] = adjustedValue;
}

double Arx::getAdjustedValue(double controlValue)
{
    addControlValue(controlValue);

    double controlSum = 0.0;
    for (size_t i = 0; i < b.size(); i++) {
        controlSum += b[i] * controlValuesBuffer[k + i];
    }
    double outputSum = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        outputSum += a[i] * adjustedValuesBuffer[i];
    }
    double adjustedValue = controlSum - outputSum;
    addAdjustedValue(adjustedValue);
    return adjustedValue;
}

void Arx::reset(){
    adjustedValuesBuffer.resize(a.size(), 0.0);
    controlValuesBuffer.resize(k + b.size(), 0.0);
}
