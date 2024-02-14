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

int graf::open_par_window(function &in)
{
    qInfo()<<"window open pressed";
    window= new par_window(in,nullptr);
    int out=window->exec();
    qInfo()<<"window exec";
    delete window;
    qInfo()<<"window delete";

    return out;
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
    QString wypisz= "type: " + type2string(it->get_type())
                     + " a = "+ QString::number(par.a) +
                     " b = "+ QString::number(par.b)
                     + " c = " +QString::number(par.c);
    ui->par_display->setHtml(wypisz);
    qInfo()<<"display end";
}

void graf::on_display_left_pressed()
{
    if(curr>0)
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
    qInfo()<<curr;
    qInfo()<<ammount;

    display_par();
}

void graf::on_create_pressed()
{
    qInfo()<<"crete bg";
    function fn;

    if(open_par_window(fn))
    {
        qInfo()<<"window closed";
        function_list.push_back(fn);
        qInfo()<<"push back";
        create_view();
        curr++;
        ammount++;
    }
    qInfo()<<"crete end";
}

//debug code//
/*
void graf::on_edit_pressed()
{
    function fn;
    qInfo()<<"edit bg";
    if(open_par_window(fn))
    {
        qInfo()<<"window closed sucesfully";

        parameters tst= fn.get_parameters();
        qInfo()<<tst.a;
        qInfo()<<tst.b;
        qInfo()<<tst.c;

        qInfo()<<type2string(fn.get_type());

        if(chart!=nullptr)
        {
            delete chart;
        }
        qInfo()<<"chart delete";

        chart = new QChart();
        qInfo()<<"new chart";

        chart->addSeries(fn.create_series());
        chart->createDefaultAxes();
        qInfo()<<"series added";

        if(view!=nullptr)
        {
            delete view;
        }
        qInfo()<<"view deleted";

        view =new QChartView(chart);
        qInfo()<<"chart added";
        view->setRenderHint(QPainter::Antialiasing);

        ui->dispay->addWidget(view,0,0);

        qInfo()<<"display widget";

        parameters par=fn.get_parameters();
        QString wypisz= "type: " + type2string(fn.get_type()) +
                         " a = "+ QString::number(par.a) +
                         " b = "+ QString::number(par.b) +
                         " c = " +QString::number(par.c);
        ui->par_display->setHtml(wypisz);
    }
}
*/

void graf::on_edit_pressed()
{
    function fn;
    if(open_par_window(fn))
    {
        auto it = function_list.begin();
        for (int i = 0; i < curr; ++i)
        {
            it++;
        }
        *it=fn;
        create_view();
    }
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
        //debug code//
        /*
        qInfo()<<it->create_series()->count();

        QList<QPointF> list=it->create_series()->points();
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            qInfo()<<it->x();
            qInfo()<<it->y();
        }
        */
        chart->addSeries(it->create_series());

        qInfo()<<"chart iter end";
        iter++;
    }
    //debug code//
    /*
    QSplineSeries *series = new QSplineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    chart->addSeries(series);
    */
    chart->createDefaultAxes();

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

