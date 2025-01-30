#ifndef FACADE_H
#define FACADE_H
//#include "mainwindow.h"
#include "Simulator.h"
#include "ARX.h"
#include "SimulatorMemento.h"
#include "SetpointGenerator.h"
#include "Feedback.h"
#include "qobject.h"
#include <vector>

class Facade : public QObject{
    Q_OBJECT
private:
    Simulator* simulator;

    QTimer* timer;


    double actualK =-1;
    double actualTi;
    double actualTd;
    double actualInterval;

    double actualConstantValue;

    double actualSinusoidalAmplitude;
    double actualSinusoidalPeriod;

    double actualSquareAmplitude;
    double actualSquarelPeriod;
    double actualSquarelDutyCycle;

    bool simulation = false;


public:
    Facade();
    void initializeSimulator();


    void setARX(vector<double> a, vector<double> b, int k);
    void setARXSettings(vector<double> a, vector<double> b, int k);
    void setPID(double k, double Ti, double Td);
    void setPIDSettings(double k, double Ti, double Td);
    void setConstantSignal(double value);
    void setSinusoidalSignal(double amplitude,double period);
    void setSquareSignal(double amplitude,double period, double dutyCycle);
    void setTimeInterval(int interval);

    void resetSimulation();
    void actualize();
    void startSimulation();
    void stopSimulation();

    void loadFromFile(QString fileName);
    void saveToFile(QString fileName);

    void setActual(double actualK,
                    double actualTi,
                    double actualTd,
                    double actualInterval,
                    double actualConstantValue,
                    double actualSinusoidalAmplitude,
                    double actualSinusoidalPeriod,
                    double actualSquareAmplitude,
                    double actualSquarelPeriod,
                    double actualSquarelDutyCycle);
    std::vector<double> getActual();

    bool isSimulatorInitialized();

    double getActualK();
    std::vector<std::tuple<double, double, double, double>> getHistory();
private slots:
    void runSimulationStep();
signals:
    void newSimulationData(double time, double generatedValue, double error, double controlValue, double adjustedValue);

};

#endif // FACADE_H


