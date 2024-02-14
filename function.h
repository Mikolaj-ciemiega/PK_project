#ifndef FUNCTION_H
#define FUNCTION_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <QtWidgets>
#include <QGraphicsView>
#include <QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QPainterPath>

enum class type_of_fun
{
    line,para,sqrt,log,sin
};

struct axis
{
    double min = 0;
    double max = 0;
};

struct parameters
{
    double a = 0, b = 0, c = 0;
};

struct point
{
    double x=0, y=0;
};

using array= point*;

class function
{
    type_of_fun type;
    parameters par;
    axis x;
    int size_of_array;
    void cal_size_of_array();

    void fun(array);
    void fun_line(array);
    void fun_para(array);
    void fun_root(array);
    void fun_log(array);
    void fun_sin(array);

    void update_par(parameters n_par);
    void update_axis(axis n_x);
    void update_type(type_of_fun n_type);
public:
    function();
    QChartView show_view();
    parameters get_parameters();
    type_of_fun get_type();
    void update_fun(parameters n_par,axis n_x,type_of_fun n_type);
    QSplineSeries* create_series();
};

#endif // FUNCTION_H
