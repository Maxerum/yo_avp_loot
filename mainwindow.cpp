#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <intrin.h>

#pragma intrinsic(__rdtsc)



using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart = new QChart;

    ui->widget->setChart(chart);

    QLineSeries *series = new QLineSeries();


            // Create chart, add data, hide legend, and add axis
//            QChart *chart = new QChart();
            chart->legend()->hide();


            // Customize the title font
            QFont font;
            font.setPixelSize(18);



            // Change the line color and weight
            QPen pen(QRgb(0x000000));
            pen.setWidth(5);
            series->setPen(pen);

//            chart->setAnimationOptions(QChart::AllAnimations);

            // Change the x axis categories
//            QCategoryAxis *axisX = new QCategoryAxis();
//            axisX->append(0);
//            axisX->append("1987",1);
//            axisX->append("1988",2);
//            axisX->append("1989",3);
//            axisX->append("1990",4);
//            axisX->append("1991",5);
//            axisX->append("1992",6);
//            chart->setAxisX(axisX, series);

            // Used to display the chart
//            QChartView *chartView = new QChartView(chart);
//            chartView->setRenderHint(QPainter::Antialiasing);

//    QValueAxis *axisX = new QValueAxis;
////    axisX->setRange(0, 20);
////    axisX->setTickCount(11);
////    axisX->setLabelFormat("%.2f");

//    QValueAxis *axisY = new QValueAxis;
////    axisY->setRange(0, 2000000000);
////    axisX->setTickCount(11);
////    axisX->setLabelFormat("%g");

//    QLineSeries* series1 = new QLineSeries();
//    QLineSeries* series2 = new QLineSeries();

    ull* array;
    float delay;
    array = new ull[OFFSET * N];
    for (int i = 1; i <= N; i++) {
         init(array, CACHE_SIZE, i);
         delay = testRead(array);
         cout << setw(2) << i << " : " << setw(8) << delay << " secs" << endl;
         series->append(i, delay);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
//    chrt->addSeries(series1);
//    chrt->addSeries(series2);
//    chrt->setAxisX(axisX, series1);
//    chrt->setAxisY(axisY, series1);
//    chrt->setAxisX(axisX, series2);
//    chrt->setAxisX(axisY, series2);

    delete[] array;

}

void MainWindow::init(ull *array, size_t size, int assoc){

    ZeroMemory(array, OFFSET * N);

    if (assoc == 1) {

        for (size_t i = 0; i < size - 1; i++) {

            array[i] = i + 1;
        }
        return;
    }

    size_t blockSize = size % assoc == 0 ? size / assoc : size / assoc + 1;
    size_t currentOffset = 0;

    for (size_t i = 0; i < assoc - 1; i++) {

        for (size_t j = 0; j < blockSize; j++)
            array[currentOffset + j] = currentOffset + OFFSET + j;

        currentOffset += OFFSET;
    }

    for (size_t i = 0; i < blockSize; i++)
        array[currentOffset + i] = i + 1;
}

float MainWindow::testRead(ull *array) {

    ull index = 0;
//    ull startTicks = __rdtsc();
    float delay;
    LARGE_INTEGER start,finish, frequency;
    QueryPerformanceCounter(&start);
    for (int i = 0; i < TRIES; i++) {

        do {
            index = array[index];
        } while (index);
    }
    QueryPerformanceCounter(&finish);
            delay = (finish.QuadPart - start.QuadPart)/100000;
//    ull endTicks = __rdtsc();
     return delay;
//    return (endTicks - startTicks)/ TRIES;
}

MainWindow::~MainWindow()
{
    delete ui;
}

