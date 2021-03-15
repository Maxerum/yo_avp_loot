#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


using namespace QtCharts;

#define KB 1024
#define MB 1024 * KB
#define CACHE_SIZE 6 * MB / sizeof(ull)
#define OFFSET 4 * MB / sizeof(ull)
#define N 20
#define TRIES 100

typedef unsigned long long int ull;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init(ull *array, size_t size, int assoc);
    float testRead(ull *array);
private:
    Ui::MainWindow *ui;
    QChart *chart;
};
#endif // MAINWINDOW_H
