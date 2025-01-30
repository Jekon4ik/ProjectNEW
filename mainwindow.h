#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "Facade.h"
#include "dialogarx.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_constantDoubleSpinBox_valueChanged(double arg1);

    void on_actionSET_triggered();

    void on_actualizeButton_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void updatePlots(double time, double generatedValue, double error, double controlValue, double adjustedValue);

    void on_resetButton_clicked();


    void on_actionSAVE_TO_FILE_triggered();

    void on_actionLOAD_FROM_FILE_triggered();

private:
    Ui::MainWindow *ui;
    Facade* facade;
    DialogARX* arxDialog;
};
#endif // MAINWINDOW_H
