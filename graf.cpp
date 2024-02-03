#include "graf.h"
#include "ui_graf.h"

graf::graf(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::graf)
{
    ui->setupUi(this);

    function show;
    parameters par; par.a=1; par.b=0, par.c=0;
    axis ax; ax.max=10; ax.min=-10;
    show.update_fun(par,ax,type_of_fun::para);
    function_list.push_back(show);
    create_view();
}

graf::~graf()
{
    delete ui;
}

void graf::open_par_window(function* in)
{
    qInfo()<<"window open pressed";
    window= new par_window(in,nullptr);
    window->exec();
    qInfo()<<"window exec";
    delete window;
    qInfo()<<"window delete";
}

QString graf:: type2string(type_of_fun type)
{
    switch (type) {
    case type_of_fun::line:
        return "line";
        break;
    case type_of_fun::para:
        return "para";
        break;
    case type_of_fun::sqrt:
        return "root";
        break;
    case type_of_fun::log:
        return "log";
        break;
    case type_of_fun::sin:
        return "sin";
        break;
    }
}

void graf::display_par()
{
    qInfo()<<"display bg";
    auto it = function_list.begin();
    for (int i = 0; i < curr; ++i)
    {
        it++;
    }
    parameters par=it->get_parameters();
    QString wypisz= "type: " + type2string(it->get_type()) + " a = "+ QString::number(par.a) +
                     " b = "+ QString::number(par.b) + " c = " +QString::number(par.c);
    ui->par_display->setHtml(wypisz);
    qInfo()<<"display end";
}

void graf::on_display_left_pressed()
{
    if(curr>1)
    {
        curr--;
    }
    display_par();
}

void graf::on_display_right_pressed()
{
    if(curr!=ammount)
    {
        curr++;
    }
    display_par();
}

void graf::on_create_pressed()
{
    qInfo()<<"crete bg";
    function *fn= new function;
    open_par_window(fn);
    qInfo()<<"window closed";
    if(fn!=nullptr)
    {
        function_list.push_back(*fn);
        qInfo()<<"push back";
        create_view();
        curr++;
        ammount++;
    }
    qInfo()<<"crete end";
    delete fn;
}

void graf::on_edit_pressed()
{
    function *fn= new function;
    open_par_window(fn);
    auto it = function_list.begin();
    for (int i = 0; i < curr; ++i)
    {
        it++;
    }
    *it=*fn;
    create_view();
    delete fn;
}

void graf::on_delete_2_pressed()
{
    auto it = function_list.begin();
    for (int i = 0; i < curr; ++i)
    {
        it++;
    }
    function_list.erase(it);
    create_view();
}

void graf::create_view()
{
    qInfo()<<"view start";
    if(chart!=nullptr)
    {
        delete chart;
    }
    qInfo()<<"chart delete";

    chart = new QChart();
    qInfo()<<"new chart";
    int iter=1;
    for (auto it = function_list.begin(); it != function_list.end(); ++it)
    {
        qInfo()<<iter;
        chart->addSeries(it->get_series());
        chart->createDefaultAxes();
        qInfo()<<"chart iter end";
        iter++;
    }
    qInfo()<<"series added";

    if(view!=nullptr)
    {
        delete view;
    }
    qInfo()<<"view deleted";

    view =new QChartView(chart);

    view->setRenderHint(QPainter::Antialiasing);

    ui->dispay->addWidget(view,0,0);
    qInfo()<<"display widget";
    display_par();
    qInfo()<<"view end";
}

