#include "Facade.h"
#include "qtimer.h"
Facade::Facade(){
    this->simulator= new Simulator();
    this->simulator->setFeedback(new Feedback());
    this->simulator->setGenerator(new SetpointGenerator());
    this->simulator->setARX(new Arx({-0.4},{0.6},1));
    this->simulator->setPID(new PID(0.5,10,0.2));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Facade::runSimulationStep);
}

void Facade::setARX(vector<double> a, vector<double> b, int k){
    if(this->simulator->getARX() != nullptr) delete this->simulator->getARX();
    Arx* arx = new Arx(a,b,k);
    this->simulator->setARX(arx);
     qDebug() << "new arx created";
}
void Facade::setARXSettings(vector<double> a, vector<double> b, int k){
    if(this->simulator->getARX() == nullptr){
        setARX(a,b,k);
    }
    else{
        this->simulator->getARX()->setA(a);
        this->simulator->getARX()->setB(b);
        this->simulator->getARX()->setK(k);
        qDebug() << "arx changed";
    }
}
void Facade::setPID(double k, double Ti, double Td){
    if(this->simulator->getPID() != nullptr) delete this->simulator->getPID();
    PID* pid = new PID(k,Ti,Td);
    this->simulator->setPID(pid);
    qDebug() << "new pid created";
}
void Facade::setPIDSettings(double k, double Ti, double Td){
    if(this->simulator->getPID() == nullptr){
        setPID(k,Ti,Td);
    }
    else{
        this->simulator->getPID()->setK(k);
        this->simulator->getPID()->setTi(Ti);
        this->simulator->getPID()->setTd(Td);
        qDebug() << "pid changed";
    }
}

void Facade::setConstantSignal(double val){
    ConstantSignal* signal = new ConstantSignal(val);
    this->simulator->changeMode(signal);
}

void Facade::setSinusoidalSignal(double amplitude,double period){
    SinusoidSignal* signal = new SinusoidSignal(amplitude,period);
    this->simulator->changeMode(signal);
}
void Facade::setSquareSignal(double amplitude,double period,double dutyCycle){
    SquareSignal* signal = new SquareSignal(amplitude,period, dutyCycle);
    this->simulator->changeMode(signal);
}

void Facade::setActual(double actualK,
                       double actualTi,
                       double actualTd,
                       double actualInterval,
                       double actualConstantValue,
                       double actualSinusoidalAmplitude,
                       double actualSinusoidalPeriod,
                       double actualSquareAmplitude,
                       double actualSquarelPeriod,
                       double actualSquarelDutyCycle)
{
    this->actualK = actualK;
    this->actualTi = actualTi;
    this->actualTd = actualTd;
    this->actualInterval = actualInterval;
    this->actualConstantValue = actualConstantValue;
    this->actualSinusoidalAmplitude = actualSinusoidalAmplitude;
    this->actualSinusoidalPeriod = actualSinusoidalPeriod;
    this->actualSquareAmplitude = actualSquareAmplitude;
    this->actualSquarelPeriod = actualSquarelPeriod;
    this->actualSquarelDutyCycle = actualSquarelDutyCycle;
}

std::vector<double> Facade::getActual() {
    std::vector<double> actualValues;

    actualValues.push_back(actualK);
    actualValues.push_back(actualTi);
    actualValues.push_back(actualTd);
    actualValues.push_back(actualInterval);
    actualValues.push_back(actualConstantValue);
    actualValues.push_back(actualSinusoidalAmplitude);
    actualValues.push_back(actualSinusoidalPeriod);
    actualValues.push_back(actualSquareAmplitude);
    actualValues.push_back(actualSquarelPeriod);
    actualValues.push_back(actualSquarelDutyCycle);

    return actualValues;
}
double Facade::getActualK(){return this->actualK;}

bool Facade::isSimulatorInitialized(){
    if(this->simulator->getARX() == nullptr) return false;
    if(this->simulator->getPID()==nullptr) return false;
    if(this->simulator->getFeedback()==nullptr) return false;
    if(this->simulator->getGenerator()==nullptr) return false;
    return true;
}

void Facade::setTimeInterval(int interval){
    this->simulator->setTimeInterval(interval);
}



void Facade::startSimulation() {
    if (!isSimulatorInitialized()) {
        qDebug() << "Simulator is not initialized!";
        return;
    }

    simulation = true;
    timer->start(this->simulator->getTimeInterval());
    qDebug() << "Simulation started with interval" << this->simulator->getTimeInterval();
}

void Facade::stopSimulation() {
    simulation = false;
    timer->stop();
    qDebug() << "Simulation stopped!";
}

void Facade::runSimulationStep() {
    if (simulation) {
        this->simulator->runSimulation();
        vector<double> values = this->simulator->getState();
        emit newSimulationData(values[0], values[1], values[1], values[2], values[3]);
        qDebug() << "from facade " << values[0] << " " << values[1] << " " << values[1] <<  values[2] << values[3];
    }
}
void Facade::resetSimulation(){
    this->simulator->resetSimulation();
    Arx* newArx = new Arx(this->simulator->getARX()->getA(),this->simulator->getARX()->getB(),this->simulator->getARX()->getK());
    if(this->simulator->getARX() != nullptr) delete this->simulator->getARX();
    this->simulator->setARX(newArx);

    if(this->simulator->getPID() != nullptr) delete this->simulator->getPID();
    this->simulator->setPID(new PID(this->simulator->getPID()->getK(),this->simulator->getPID()->getTi(),this->simulator->getPID()->getTd()));

    delete this->simulator->getFeedback();
    this->simulator->setFeedback(new Feedback());
    delete this->simulator->getGenerator();
    this->simulator->setGenerator(new SetpointGenerator());
}

void Facade::saveToFile(QString filename){
    this->simulator->saveToFile(filename.toStdString());
}

void Facade::loadFromFile(QString filename){
    this->simulator->loadFromFile(filename.toStdString());
    setARX(this->simulator->getArxASettings(),this->simulator->getArxBSettings(), this->simulator->getArxKSettings());
    std::vector<double> temp = this->simulator->getPidSettings();
    setPID(temp[0],temp[1],temp[2]);
}
std::vector<std::tuple<double, double, double, double>> Facade::getHistory()
{
    return this->simulator->getHistory();
}
