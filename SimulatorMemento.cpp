#include "SimulatorMemento.h"
#include <iostream>
SimulatorMemento::SimulatorMemento(
    int time,
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
    const std::vector<std::tuple<double, double, double, double>> &history)
    : time(time)
    , error(error)
    , generatedValue(generatedValue)
    , adjustedValue(adjustedValue)
    , controlValue(controlValue)
    , arxA(arxA)
    , arxB(arxB)
    , arxK(arxK)
    , pidK(pidK)
    , pidTi(pidTi)
    , pidTd(pidTd)
    , history(history)
{}

std::string SimulatorMemento::serialize() const
{
    std::ostringstream oss;

    // Serialize basic data
    oss << time << " " << error << " " << generatedValue << " " << adjustedValue << " "
        << controlValue << "\n";

    // Serialize ARX settings
    oss << arxA.size() << " ";
    for (double a : arxA)
        oss << a << " ";
    oss << arxB.size() << " ";
    for (double b : arxB)
        oss << b << " ";
    oss << arxK << "\n";

    // Serialize PID settings
    oss << pidK << " " << pidTi << " " << pidTd << "\n";

    // Serialize history
    oss << history.size() << "\n";
    for (const auto &[genValue, err, ctrlValue, adjValue] : history) {
        oss << genValue << " " << err << " " << ctrlValue << " " << adjValue << "\n";
    }

    return oss.str();
}

SimulatorMemento SimulatorMemento::deserialize(const std::string &data)
{
    std::istringstream iss(data);
    int time, arxK, arxASize, arxBSize, historySize;
    double error, generatedValue, adjustedValue, controlValue, pidK, pidTi, pidTd;

    // Deserialize basic data
    if (!(iss >> time >> error >> generatedValue >> adjustedValue >> controlValue)) {
        throw std::runtime_error("Failed to read basic simulation state.");
    }

    // Deserialize ARX settings
    if (!(iss >> arxASize) || arxASize < 0) {
        throw std::runtime_error("Invalid ARX A size.");
    }
    std::vector<double> arxA(arxASize);
    for (int i = 0; i < arxASize; ++i) {
        if (!(iss >> arxA[i])) {
            throw std::runtime_error("Failed to read ARX A coefficients.");
        }
    }

    if (!(iss >> arxBSize) || arxBSize < 0) {
        throw std::runtime_error("Invalid ARX B size.");
    }
    std::vector<double> arxB(arxBSize);
    for (int i = 0; i < arxBSize; ++i) {
        if (!(iss >> arxB[i])) {
            throw std::runtime_error("Failed to read ARX B coefficients.");
        }
    }

    if (!(iss >> arxK)) {
        throw std::runtime_error("Failed to read ARX K value.");
    }

    // Deserialize PID settings
    if (!(iss >> pidK >> pidTi >> pidTd)) {
        throw std::runtime_error("Failed to read PID settings.");
    }

    // Deserialize history
    if (!(iss >> historySize) || historySize < 0) {
        throw std::runtime_error("Invalid history size.");
    }
    std::vector<std::tuple<double, double, double, double>> history(historySize);
    for (int i = 0; i < historySize; ++i) {
        double genValue, err, ctrlValue, adjValue;
        if (!(iss >> genValue >> err >> ctrlValue >> adjValue)) {
            throw std::runtime_error("Failed to read history entry.");
        }
        history[i] = {genValue, err, ctrlValue, adjValue};
    }

    return SimulatorMemento(time,
                            generatedValue,
                            error,
                            controlValue,
                            adjustedValue,
                            arxA,
                            arxB,
                            arxK,
                            pidK,
                            pidTi,
                            pidTd,
                            history);
}

const std::vector<double> &SimulatorMemento::getArxA() const
{
    return arxA;
}
const std::vector<double> &SimulatorMemento::getArxB() const
{
    return arxB;
}
int SimulatorMemento::getArxK() const
{
    return arxK;
}
double SimulatorMemento::getPidK() const
{
    return pidK;
}
double SimulatorMemento::getPidTi() const
{
    return pidTi;
}
double SimulatorMemento::getPidTd() const
{
    return pidTd;
}

const std::vector<std::tuple<double, double, double, double>> &SimulatorMemento::getHistory() const
{
    return history;
}
