#include "par_window.h"
#include "ui_par_window.h"

par_window::par_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::par_window), out_data(nullptr)
{
    ui->setupUi(this);
    connect(this,SIGNAL(finished(int)),
            this,SLOT(on_finished(int)));
}

par_window::par_window(function &i_out_data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::par_window), out_data(&i_out_data)
{
    ui->setupUi(this);
}

par_window::~par_window()
{
    delete ui;
}

void par_window::on_push_line_pressed()
{
    type=type_of_fun::line;
    ui->par_c->setDisabled(1);
    ui->txt_show_type->setHtml("line");
    on_par_b_valueChanged(1);
}

void par_window::on_push_para_pressed()
{
    type=type_of_fun::para;
    ui->par_c->setDisabled(0);
    ui->txt_show_type->setHtml("parabola");
    on_par_b_valueChanged(1);
}

void par_window::on_push_root_pressed()
{
    type=type_of_fun::sqrt;
    ui->par_c->setDisabled(0);
    ui->txt_show_type->setHtml("root");
    on_par_b_valueChanged(1);
}

void par_window::on_push_log_pressed()
{
    type=type_of_fun::log;
    ui->par_c->setDisabled(0);
    ui->txt_show_type->setHtml("log");
    on_par_b_valueChanged(1);
}

void par_window::on_push_sin_pressed()
{
    type=type_of_fun::sin;
    ui->par_c->setDisabled(0);
    ui->txt_show_type->setHtml("sin");
    on_par_b_valueChanged(1);
}

void par_window::get_para()
{
    para.a=ui->par_a->value();
    para.b=ui->par_b->value();
    para.c=ui->par_c->value();
}

void par_window::on_buttonBox_accepted()
{
    get_para();
    axis ax;
    ax.min=ui->axis_min->value();
    ax.max=ui->axis_max->value();

    qInfo()<<"paramerers";
    qInfo()<<para.a;
    qInfo()<<para.b;
    qInfo()<<para.c;

    qInfo()<<"axis";
    qInfo()<<ax.min;
    qInfo()<<ax.max;

    if(ax.max < ax.min)
    {
        double d=ax.min;
        ax.min=ax.max;
        ax.max=d;
    }

    out_data->update_fun(para,ax,type);
}


void par_window::on_buttonBox_rejected()
{
    out_data=nullptr;
}


void par_window::on_par_b_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if(type==type_of_fun::log)
    {
        if(ui->par_b->value()==1.0||ui->par_b->value()<=0.0)
        {
            ui->buttonBox->setDisabled(true);

        }
        else
        {
            ui->buttonBox->setDisabled(false);
        }
    }
    else
    {
        ui->buttonBox->setDisabled(false);
    }
}

