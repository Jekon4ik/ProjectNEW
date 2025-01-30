#ifndef DIALOGARX_H
#define DIALOGARX_H

#include <QDialog>
#include <vector>
namespace Ui {
class DialogARX;
}

class DialogARX : public QDialog
{
    Q_OBJECT

public:
    explicit DialogARX(QWidget *parent = nullptr);
    ~DialogARX();
    std::vector<double> getA();
    std::vector<double> getB();
    int getK();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DialogARX *ui;
};

#endif // DIALOGARX_H
