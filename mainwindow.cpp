#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    facade = new Facade();
    ui->setupUi(this);
    ui->mainPlot->addGraph();
    ui->mainPlot->addGraph();
    ui->mainPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->mainPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->mainPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->mainPlot->xAxis->setLabel("Time");
    ui->mainPlot->xAxis->setRange(0, 100);
    ui->mainPlot->yAxis->setRange(-10, 10);
    ui->mainPlot->graph(0)->setPen(QPen(Qt::green));
    ui->mainPlot->graph(1)->setPen(QPen(Qt::red));
    ui->mainPlot->plotLayout()->insertRow(0);
    ui->mainPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->mainPlot, "Main Plot", QFont("sans", 12, QFont::Bold)));
    ui->mainPlot->legend->setVisible(true);
    ui->mainPlot->legend->setFont(QFont("sans", 10));
    ui->mainPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 150))); // Transparent white background

    // Assign names to graphs
    ui->mainPlot->graph(0)->setName("Generator"); // Green graph
    ui->mainPlot->graph(1)->setName("ARX");  // Red graph

    ui->errorPlot->addGraph();
    ui->errorPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->errorPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->errorPlot->xAxis->setLabel("Time");
    ui->errorPlot->xAxis->setRange(0, 100);
    ui->errorPlot->yAxis->setRange(-10, 10);
    ui->errorPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->errorPlot->plotLayout()->insertRow(0);
    ui->errorPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->errorPlot, "PID", QFont("sans", 12, QFont::Bold)));

    ui->pidPlot->addGraph();
    ui->pidPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->pidPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->pidPlot->xAxis->setLabel("Time");
    ui->pidPlot->xAxis->setRange(0, 100);
    ui->pidPlot->yAxis->setRange(-10, 10);
    ui->pidPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->pidPlot->plotLayout()->insertRow(0);
    ui->pidPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->pidPlot, "ERROR", QFont("sans", 12, QFont::Bold)));
    connect(facade, &Facade::newSimulationData, this, &MainWindow::updatePlots);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updatePlots(
    double time, double generatedValue, double error, double controlValue, double adjustedValue)
{
    // Update mainPlot
    ui->mainPlot->graph(0)->addData(time, generatedValue);
    ui->mainPlot->graph(1)->addData(time, adjustedValue);

    double marginX = 5.0; //margin for x axis
    if (time > 50)
        ui->mainPlot->xAxis->setRange(time - 50, time+marginX); // Auto-scroll

    double yMin = ui->mainPlot->yAxis->range().lower;
    double yMax = ui->mainPlot->yAxis->range().upper;

    if(generatedValue < yMin || adjustedValue > yMax){
        yMin -= 12;
    }
    if(generatedValue > yMax || adjustedValue > yMax){
        yMax +=12;
    }
    ui->mainPlot->yAxis->setRange(yMin, yMax);
    ui->mainPlot->replot();
    //ui->mainPlot->update();

    //Update errorPlot
    ui->errorPlot->graph(0)->addData(time, error);
    ui->errorPlot->xAxis->setRange(time - 50, time + marginX);
    double errorMin = ui->errorPlot->yAxis->range().lower;
    double errorMax = ui->errorPlot->yAxis->range().upper;
    if(error < errorMin){ errorMin -= 12; }
    if(error> errorMax){ errorMax += 12; }

    ui->errorPlot->yAxis->setRange(errorMin, errorMax);
    ui->errorPlot->replot();

    //Update pidPlot
    ui->pidPlot->graph(0)->addData(time, controlValue);
    ui->pidPlot->xAxis->setRange(time - 50, time + marginX);

    double pidMin = ui->pidPlot->yAxis->range().lower;
    double pidMax = ui->pidPlot->yAxis->range().upper;

    if(controlValue < pidMin){ pidMin -= 12;}
    if(controlValue > pidMax) {pidMax +=12;}

    ui->pidPlot->yAxis->setRange(pidMin, pidMax);
    ui->pidPlot->replot();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->constantDoubleSpinBox->setValue(position);
}

void MainWindow::on_constantDoubleSpinBox_valueChanged(double arg1)
{
    ui->horizontalSlider->setValue(arg1);
}

void MainWindow::on_actionSET_triggered()
{
    std::vector<double> A;
    std::vector<double> B;
    int k;
    arxDialog = new DialogARX(nullptr);
    if (arxDialog->exec() == QDialog::Accepted) {
        A = arxDialog->getA();
        B = arxDialog->getB();
        k = arxDialog->getK();
        qDebug() << B[0];
        //facade->setARXSettings(A, B, k);
        facade->setARX(A,B,k);
    }
    delete arxDialog;
}

void MainWindow::on_actualizeButton_clicked()
{
    if (facade->getActualK() == -1) {
        facade->setActual(ui->kDoubleSpinBox->value(),
                          ui->tiDoubleSpinBox_2->value(),
                          ui->tdDoubleSpinBox_3->value(),
                          ui->timeIntervalSpinBox->value(),
                          ui->constantDoubleSpinBox->value(),
                          ui->amplitudeSinusoidalDoubleSpinBox->value(),
                          ui->periodSinusoidalDoubleSpinBox_2->value(),
                          ui->amplitudeSquareDoubleSpinBox_3->value(),
                          ui->periodSquareDoubleSpinBox_4->value(),
                          ui->dutyCycleSquareDoubleSpinBox_5->value());
    }
    facade->stopSimulation();
    facade->setPIDSettings(ui->kDoubleSpinBox->value(),
                           ui->tiDoubleSpinBox_2->value(),
                           ui->tdDoubleSpinBox_3->value());
    //facade->setPID(ui->kDoubleSpinBox->value(),ui->tiDoubleSpinBox_2->value(),ui->tdDoubleSpinBox_3->value());
    facade->setTimeInterval(ui->timeIntervalSpinBox->value());
    if (ui->manualRadioButton->isChecked()) {
        facade->setConstantSignal(ui->constantDoubleSpinBox->value());
    } else if (ui->sinusoidalRadioButton_2->isChecked()) {
        facade->setSinusoidalSignal(ui->amplitudeSinusoidalDoubleSpinBox->value(),
                                    ui->periodSinusoidalDoubleSpinBox_2->value());
    } else if (ui->squareRadioButton_3->isChecked()) {
        facade->setSquareSignal(ui->amplitudeSquareDoubleSpinBox_3->value(),
                                ui->periodSquareDoubleSpinBox_4->value(),
                                ui->dutyCycleSquareDoubleSpinBox_5->value());
    } else {
        qDebug() << "Choose type of Signal";
        return;
    }
    facade->setActual(ui->kDoubleSpinBox->value(),
                      ui->tiDoubleSpinBox_2->value(),
                      ui->tdDoubleSpinBox_3->value(),
                      ui->timeIntervalSpinBox->value(),
                      ui->constantDoubleSpinBox->value(),
                      ui->amplitudeSinusoidalDoubleSpinBox->value(),
                      ui->periodSinusoidalDoubleSpinBox_2->value(),
                      ui->amplitudeSquareDoubleSpinBox_3->value(),
                      ui->periodSquareDoubleSpinBox_4->value(),
                      ui->dutyCycleSquareDoubleSpinBox_5->value());
    facade->startSimulation();
}

void MainWindow::on_startButton_clicked()
{
    if (ui->manualRadioButton->isChecked() == true
        || ui->sinusoidalRadioButton_2->isChecked() == true
        || ui->squareRadioButton_3->isChecked() == true) {
        on_actualizeButton_clicked();
        facade->startSimulation();
    } else {
        qDebug() << "Choose type of Signal";
        return;
    }
}

void MainWindow::on_stopButton_clicked()
{
    facade->stopSimulation();
}

void MainWindow::on_resetButton_clicked()
{
    facade->stopSimulation();
    facade->resetSimulation();
    ui->mainPlot->graph(0)->data()->clear();
    ui->mainPlot->graph(1)->data()->clear();
    ui->errorPlot->graph(0)->data()->clear();
    ui->pidPlot->graph(0)->data()->clear();

    //ui->mainPlot->rescaleAxes();
    ui->mainPlot->xAxis->setRange(0, 100);
    ui->mainPlot->yAxis->setRange(-10, 10);

    ui->errorPlot->xAxis->setRange(0, 100);
    ui->errorPlot->yAxis->setRange(-10, 10);

    ui->pidPlot->xAxis->setRange(0, 100);
    ui->pidPlot->yAxis->setRange(-10, 10);

    // Optionally, replot the charts
    ui->mainPlot->replot();
    ui->errorPlot->replot();
    ui->pidPlot->replot();

    ui->mainPlot->update();
    ui->errorPlot->update();
    ui->pidPlot->update();
}

void MainWindow::on_actionSAVE_TO_FILE_triggered()
{
    facade->stopSimulation();
    QString fileName = QFileDialog::getSaveFileName(this, "SAVE TO FILE");
    facade->stopSimulation();
    facade->saveToFile(fileName);
}

void MainWindow::on_actionLOAD_FROM_FILE_triggered()
{
    on_resetButton_clicked();
    qDebug() << "lol";
    QString fileName = QFileDialog::getOpenFileName(this, "LOAD FROM FILE");
    facade->loadFromFile(fileName);
    //load data from vector
    auto history = facade->getHistory();
    double time = 0;
    for (const auto &[generatedValue, error, controlValue, adjustedValue] : history) {
        ui->mainPlot->graph(0)->addData(time, generatedValue);
        ui->mainPlot->graph(1)->addData(time, adjustedValue);
        ui->errorPlot->graph(0)->addData(time, error);
        ui->pidPlot->graph(0)->addData(time, controlValue);

        time++;
    }
    ui->mainPlot->replot();
    ui->errorPlot->replot();
    ui->pidPlot->replot();
    ui->mainPlot->update();
    ui->errorPlot->update();
    ui->pidPlot->update();
}
