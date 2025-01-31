#define _USE_MATH_DEFINES
#pragma once
#include <QDebug>
#include "ARX.h"
#include "Feedback.h"
#include "PIDRegulator.h"
#include "SetpointGenerator.h"
#include "SimulatorMemento.h"
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class Simulator
{
private:
    int time = 0;

    Arx *arx = nullptr;
    PID *pid = nullptr;
    Feedback *feedback = nullptr;
    SetpointGenerator *setpointGenerator = nullptr;
    int timeInterval = 0;
    bool isSimulationgRunning = false;

    double error = 0;
    double generatedValue = 0;
    double adjustedValue = 0;
    double controlValue = 0;

    void setState(double generatedValue, double error, double controlValue, double adjustedValue);
    void timeSleep(int interval);
    std::vector<std::tuple<double, double, double, double>> generationHistory;

    std::vector<double> arxASettings;
    std::vector<double> arxBSettings;
    double arxKSettings;
    std::vector<double> pidSettings = vector<double>(3);

public:
    Simulator();
    Simulator(Arx *arx, PID *pid, Feedback *feedback, SetpointGenerator *setpointGenerator);
    void runSimulation();
    void stopSimulation();
    void resetSimulation();

    void changeMode(SignalStrategy *strategy);

    SimulatorMemento saveState();

    void restoreState(const SimulatorMemento &memento);

    void saveToFile(const std::string &filename);
    vector<double> getState();
    void loadFromFile(const std::string &filename);

    double getTime() const;
    double getError() const;
    double getRegulatedValue() const;
    double getControllValue() const;
    std::vector<double> getArxASettings();
    std::vector<double> getArxBSettings();
    int getArxKSettings();
    std::vector<double> getPidSettings();

    void setTime() const;
    void setError();
    void setGeneratedValue();
    void setControllValue();

    void setARX(Arx *arx);
    void setPID(PID *pid);
    void setFeedback(Feedback *fb);
    void setGenerator(SetpointGenerator *generator);
    void setTimeInterval(int interval);

    Arx *getARX();
    PID *getPID();
    Feedback *getFeedback();
    SetpointGenerator *getGenerator();
    int getTimeInterval();

    std::shared_ptr<Arx> getARXSettings();
    std::shared_ptr<PID> getPIDSettings();
    std::vector<std::tuple<double, double, double, double>> getHistory();
};
