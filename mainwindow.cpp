#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <intrin.h>

#pragma intrinsic(__rdtsc)

struct CacheSize
{
    size_t size;
    size_t lineSize;
};

int* arrray;
int offset = 1 * 1024 * 1024;
int const maxWay = 20;

CacheSize getCacheSize(int level) {
    CacheSize cacheLevel;
    cacheLevel.lineSize = 0;
    cacheLevel.size = 0;
    DWORD bufferSize = 0;
    DWORD i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

    GetLogicalProcessorInformation(0, &bufferSize);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(bufferSize);
    GetLogicalProcessorInformation(&buffer[0], &bufferSize);

    for (i = 0; i != bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
        if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == level) {
            cacheLevel.size = buffer[i].Cache.Size;
            cacheLevel.lineSize = buffer[i].Cache.LineSize;
            break;
        }
    }

    free(buffer);
    return cacheLevel;
}


int cacheSize = (int)(getCacheSize(1).size);

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart = new QChart;

    ui->widget->setChart(chart);

    QLineSeries *series = new QLineSeries();
    chart->legend()->hide();


    QFont font;
    font.setPixelSize(18);

    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
     series->setPen(pen);

   cout << "Cache Size: " << cacheSize << " Bytes." << endl;

   arrray = (int*)malloc(offset * maxWay * sizeof(int));

    double timerArray[maxWay];
    register unsigned long long startTicks = 0;
    register unsigned long long endTicks = 0;
    register unsigned long long resultTicks = 0;
    register int index = 0;

    for (int i = 1; i <= maxWay; i++) {
        startTicks = 0;
        endTicks = 0;
        index = 0;

        init(cacheSize / i, offset, i);//инициализируем массив размером, который будет составлять часть размера кэш-памяти , смещение между блоками,

        startTicks = __rdtsc();
        for (int i = 1; i <= maxWay; i++) {
            do {
                index = arrray[index];
            } while (index != 0);
        }
        endTicks = __rdtsc();

        resultTicks = endTicks - startTicks;
        timerArray[i - 1] = (double)(resultTicks) ;
        series->append(i, (double)(resultTicks));

    }

    show_time(timerArray);
    chart->addSeries(series);
    chart->createDefaultAxes();

}

void MainWindow::init(int blockSize, int offset, int n){
    for (int i = 0; i < blockSize; i++) {
            for (int j = 0; j < n; j++) {
                if (j < n - 1) {
                    arrray[j * offset + i] = (j + 1) * offset + i;
                }
                else if (i < blockSize - 1) {
                    arrray[j * offset + i] = i + 1;
                }
                else {
                    arrray[j * offset + i] = 0;
                }
            }
        }
}


void MainWindow::show_time(double* timerArray) {
    double value = 0;

    for (int i = 0; i < maxWay; i++) {
        printf("%02i ", i + 1);

        value = 0.0;
        printf("Time - %.0lf ticks\n", timerArray[i]);
    }
}




MainWindow::~MainWindow()
{
    delete ui;
}
