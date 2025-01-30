#define _USE_MATH_DEFINES
#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <vector>

class Feedback
{
    double measuredValue = 0;
    double generatedValue = 0;

public:
    void setGeneratedValue(double generatedValue);
    void setMeasuredValue(double measuredValue);
    double getError();
    void reset();
};
