#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


using namespace QtCharts;

#pragma intrinsic(__rdtsc)
using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init(int blockSize, int offset, int n);
    void show_time(double* timerArray);

//    float testRead(ull *array);
private:
    Ui::MainWindow *ui;
    QChart *chart;
};
#endif // MAINWINDOW_H
