#include "Simulator.h"

void Simulator::setState(double generatedValue,
                         double error,
                         double controlValue,
                         double adjustedValue)
{
    this->generatedValue = generatedValue;
    this->error = error;
    this->controlValue = controlValue;
    this->adjustedValue = adjustedValue;
}

vector<double> Simulator::getState(){
    vector<double> values = {
        static_cast<double>(this->time),
        static_cast<double>(this->generatedValue),
        static_cast<double>(this->error),
        static_cast<double>(this->controlValue),
        static_cast<double>(this->adjustedValue)
    };
    return values;
}

void Simulator::timeSleep(int interval)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
}

Simulator::Simulator()
{
    this->arx = nullptr;
    this->pid = nullptr;
    this->feedback = nullptr;
    this->setpointGenerator = nullptr;
}

Simulator::Simulator(Arx *arx, PID *pid, Feedback *feedback, SetpointGenerator *setpointGenerator)
{
    this->arx = arx;
    this->pid = pid;
    this->feedback = feedback;
    this->setpointGenerator = setpointGenerator;
}
void Simulator::setARX(Arx* arx){
    this->arx = arx;
}
void Simulator::setPID(PID* pid){
    this->pid = pid;
}
void Simulator::setFeedback(Feedback* fb){
    this->feedback = fb;
}
void Simulator::setGenerator(SetpointGenerator* generator){
    this->setpointGenerator = generator;
}
void Simulator::setTimeInterval(int interval){
    this->timeInterval = interval;
}

void Simulator::runSimulation()
{
    this->isSimulationgRunning = true;

    double generatedValue = this->setpointGenerator->generate(this->time);
    feedback->setGeneratedValue(generatedValue);
    double error = feedback->getError();
    double controlValue = pid->getControlledValue(error);
    double adjustedValue = arx->getAdjustedValue(controlValue);
    this->feedback->setMeasuredValue(adjustedValue);
    generationHistory.emplace_back(generatedValue, error, controlValue, adjustedValue);

    qDebug() << "time = " << time << " w = " << generatedValue << "; error = " << feedback->getError()
             << "; u = " << controlValue << "; y = " << adjustedValue << "Time Interval = " << this->timeInterval;
    this->time++;
    setState(generatedValue, error, controlValue, adjustedValue);
    //timeSleep(this->timeInterval);
}
void Simulator::stopSimulation()
{
    this->isSimulationgRunning = false;
}
void Simulator::resetSimulation()
{
    this->isSimulationgRunning = false;
    this->time = 0;
    generationHistory.resize(0);
}

void Simulator::changeMode(SignalStrategy *strategy)
{
    this->setpointGenerator->setStrategy(strategy);
}

SimulatorMemento Simulator::saveState()
{
    // Collect ARX settings
    std::vector<double> arxA = arx->getA();
    std::vector<double> arxB = arx->getB();
    int arxK = arx->getK();

    // Collect PID settings
    double pidK = pid->getK();
    double pidTi = pid->getTi();
    double pidTd = pid->getTd();

    // Prepare the history vector (up to 150 entries)
    std::vector<std::tuple<double, double, double, double>> history = generationHistory;

    // Create and return the memento
    return SimulatorMemento(this->time,
                            this->generatedValue,
                            this->error,
                            this->controlValue,
                            this->adjustedValue,
                            arxA,
                            arxB,
                            arxK,
                            pidK,
                            pidTi,
                            pidTd,
                            history);
}

void Simulator::restoreState(const SimulatorMemento &memento)
{
    //cout << " null" << endl;
    if(this->setpointGenerator == nullptr) cout << "setpoint null" << endl;
    if(this->arx == nullptr) cout << "arx null" << endl;
    if(this->pid == nullptr) cout << "pid null" << endl;
    if(this->feedback == nullptr) cout << "feedback null" << endl;

    this->time = memento.getTime();
    feedback->setGeneratedValue(memento.getGeneratedValue());
    feedback->setMeasuredValue(memento.getAdjustedValue());
    this->error = memento.getError();
    this->controlValue = memento.getControlValue();
}

void Simulator::saveToFile(const std::string &filename)
{
    // Collect ARX and PID settings
    std::vector<double> arxA = arx->getA();
    std::vector<double> arxB = arx->getB();
    int arxK = arx->getK();

    double pidK = pid->getK();
    double pidTi = pid->getTi();
    double pidTd = pid->getTd();

    // Create the history vector
    std::vector<std::tuple<double, double, double, double>> history = generationHistory;

    // Create the memento
    SimulatorMemento memento(this->time,
                             this->generatedValue,
                             this->error,
                             this->controlValue,
                             this->adjustedValue,
                             arxA,
                             arxB,
                             arxK,
                             pidK,
                             pidTi,
                             pidTd,
                             history);

    // Save to file
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << memento.serialize();
        ofs.close();
    } else {
        qDebug() << "Failed to open file for saving.";
        throw std::runtime_error("Failed to open file for saving.");
    }
}

void Simulator::loadFromFile(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        std::string data;
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        data = buffer.str();
        ifs.close();

        SimulatorMemento memento = SimulatorMemento::deserialize(data);

        this->time = memento.getTime();
        this->generatedValue = memento.getGeneratedValue();
        this->error = memento.getError();
        this->controlValue = memento.getControlValue();
        this->adjustedValue = memento.getAdjustedValue();

        qDebug() <<"Memento readed: time "<< memento.getTime() << " " << memento.getGeneratedValue() << " " << memento.getError()
             << " " << memento.getControlValue() << " " << memento.getAdjustedValue();


        arxASettings = memento.getArxA();
        arxBSettings = memento.getArxB();
        arxKSettings = memento.getArxK();
        pidSettings[0] = memento.getPidK();
        pidSettings[1] =memento.getPidTi();
        pidSettings[2] = memento.getPidTd();

        this->generationHistory = memento.getHistory();

    } else {
        throw std::runtime_error("Failed to open file for loading.");
    }
}

double Simulator::getTime() const
{
    return this->time;
}

double Simulator::getError() const
{
    return this->error;
}

double Simulator::getRegulatedValue() const
{
    return adjustedValue;
}

double Simulator::getControllValue() const
{
    return controlValue;
}
int Simulator::getTimeInterval(){
    return this->timeInterval;
}

Arx* Simulator::getARX() {return this->arx;}
PID* Simulator::getPID() {return this->pid;}
Feedback* Simulator::getFeedback() {return this->feedback;}
SetpointGenerator*  Simulator::getGenerator() {return this->setpointGenerator;}

std::shared_ptr<Arx> Simulator::getARXSettings()
{
    std::vector<double> a = this->arx->getA();
    std::vector<double> b = this->arx->getB();
    int k_value = this->arx->getK();
    return std::make_shared<Arx>(a, b, k_value);
}
std::shared_ptr<PID> Simulator::getPIDSettings()
{
    double k = this->pid->getK();
    double ti = this->pid->getTi();
    double td = this->pid->getTd();

    return std::make_shared<PID>(k, ti, td);
}
std::vector<double> Simulator::getArxASettings(){return this->arxASettings;}
std::vector<double> Simulator::getArxBSettings(){return this->arxBSettings;}
int Simulator::getArxKSettings(){return this->arxKSettings;}

std::vector<double> Simulator::getPidSettings() { return this->pidSettings;}

std::vector<std::tuple<double, double, double, double>> Simulator::getHistory()
{
    return this->generationHistory;
}
