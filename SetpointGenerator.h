#define _USE_MATH_DEFINES
#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class SignalStrategy
{
public:
    virtual ~SignalStrategy() = default;
    virtual double generateSignal(int time) = 0;
};

class ConstantSignal : public SignalStrategy
{
private:
    double value;

public:
    explicit ConstantSignal(double value);
    double generateSignal(int time) override;
};

class SinusoidSignal : public SignalStrategy
{
private:
    double amplitude;
    double period;

public:
    SinusoidSignal(double amplitude, double period);
    double generateSignal(int time) override;
};

class SquareSignal : public SignalStrategy
{
private:
    double amplitude;
    double period;
    double dutyCycle;

public:
    SquareSignal(double amplitude, double period, double dutyCycle);
    double generateSignal(int time);
};

class SetpointGenerator
{
private:
    SignalStrategy *strategy = nullptr;

public:
    void setStrategy(SignalStrategy *strategy);
    double generate(int time) const;
};
