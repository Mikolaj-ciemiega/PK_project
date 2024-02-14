#include "function.h"

function::function() {}


QSplineSeries* function::create_series()
{
    qInfo()<<"create series start";

    array data = new point[size_of_array];

    /*
    QList<QPointF> list;
    QPointF point;

    double cal_x = x.min;

    for (int i = 0; i < size_of_array; ++i)
    {
        point.setX(cal_x);
        point.setY(par.a * cal_x*cal_x + par.b * cal_x + par.c);
        list.append(point);
        cal_x += 0.1;
    }
    */
    qInfo()<<"fun start";
    fun(data);
    qInfo()<<"fun end";
    QSplineSeries* series = new QSplineSeries;
    qInfo()<<"series iter";

    for (int i = 0; i < size_of_array; ++i)
    {
        series->append(data[i].x, data[i].y);
    }
    /*
    series->clear();

    series->append(list);
    */
    qInfo()<<"series iter end";
    delete[] data;
    qInfo()<<"series end";

    return series;
}

void function::update_par(parameters n_par)
{
    par.a=n_par.a;
    par.b=n_par.b;
    par.c=n_par.c;
}

void function::update_axis(axis n_x)
{
    x.min=n_x.min;
    x.max=n_x.max;

    cal_size_of_array();
}

void function::cal_size_of_array()
{
    qInfo()<<"cal size of array";
    size_of_array=x.max - x.min;
    if(size_of_array < 0) { size_of_array *= -1; }
    size_of_array*=10;
    size_of_array+=1;
    qInfo()<<size_of_array;
}

void function::update_type(type_of_fun n_type)
{
    type=n_type;
}

void function::update_fun(parameters n_par,axis n_x,type_of_fun n_type)
{
    update_par(n_par);
    qInfo()<<"par update";
    update_axis(n_x);
    qInfo()<<"ax update";
    update_type(n_type);
    qInfo()<<"type update";
    create_series();
    qInfo()<<"series update";
}

void function::fun(array data)
{
    switch (type)
    {
        case type_of_fun::line:
            fun_line(data);
            break;
        case type_of_fun::para:
            fun_para(data);
            break;
        case type_of_fun::sqrt:
            fun_root(data);
            break;
        case type_of_fun::log:
            fun_log(data);
            break;
        case type_of_fun::sin:
            fun_sin(data);
            break;
    }
}

void function::fun_line(array data)
{
    qInfo()<<"fun line";
    double cal_x = x.min;
    for (int i = 0; i < size_of_array; i++)
    { 
        data[i].x = cal_x;
        data[i].y = par.a * cal_x + par.b;
        cal_x += 0.1;


        qInfo()<<data[i].x;
        qInfo()<<data[i].y;
    }
}

void function::fun_para(array data)
{
    qInfo()<<"fun para";
    double cal_x = x.min;
    for (int i = 0; i < size_of_array; ++i)
    {
        data[i].x = cal_x;
        data[i].y = par.a * cal_x*cal_x + par.b * cal_x + par.c;
        cal_x += 0.1;
    }
}

void function::fun_root(array data)
{
    qInfo()<<"fun root";
    double cal_x = x.min;
    for (int i = 0; i < size_of_array; i++)
    {
        if(cal_x>=0)
        {
            data[i].x = cal_x;
            data[i].y = par.a*(pow(cal_x,(float)1/par.b))+par.c;
        }
        else
        {
            data[i].x = 0;
            data[i].y = 0;
        }
        cal_x += 0.1;
    }
}

void function::fun_log(array data)
{
    qInfo()<<"fun log";
    double cal_x = x.min;
    for (int i = 0; i < size_of_array; i++)
    {
        if(cal_x >= 0)
        {
        data[i].x = cal_x;
        data[i].y =par.a * (log(cal_x)/log(par.b))+par.c;
        }
        else
        {
            data[i].x = 0;
            data[i].y = 0;
        }
        cal_x += 0.1;
    }
}

void function::fun_sin(array data)
{
    qInfo()<<"fun sin";
    double cal_x = x.min;
    for (int i = 0; i < size_of_array; i++)
    {
        data[i].x = cal_x;
        data[i].y =par.a*sin(cal_x+par.b)+par.c;
        cal_x += 0.1;
    }
}

parameters function::get_parameters()
{
    return par;
}

type_of_fun function::get_type()
{
    return type;
}

