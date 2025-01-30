#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class SimulatorMemento
{
private:
    int time;

    double error;
    double generatedValue;
    double adjustedValue;
    double controlValue;
    std::vector<double> arxA;
    std::vector<double> arxB;
    int arxK;
    double pidK, pidTi, pidTd;
    std::vector<std::tuple<double, double, double, double>> history;

public:
    SimulatorMemento(int time,
                     double generatedValue,
                     double error,
                     double controlValue,
                     double adjustedValue,
                     const std::vector<double> &arxA,
                     const std::vector<double> &arxB,
                     int arxK,
                     double pidK,
                     double pidTi,
                     double pidTd,
                     const std::vector<std::tuple<double, double, double, double>> &history);

    std::string serialize() const;

    static SimulatorMemento deserialize(const std::string &data);

    int getTime() const { return time; }
    double getError() const { return error; }
    double getGeneratedValue() const { return generatedValue; }
    double getAdjustedValue() const { return adjustedValue; }
    double getControlValue() const { return controlValue; }
    const std::vector<double> &getArxA() const;
    const std::vector<double> &getArxB() const;
    int getArxK() const;
    double getPidK() const;
    double getPidTi() const;
    double getPidTd() const;

    const std::vector<std::tuple<double, double, double, double>> &getHistory() const;
};
